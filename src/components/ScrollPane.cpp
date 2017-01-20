//
//  ScrollPane.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 6/24/14.
//
//

#include "ScrollPane.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel {

    ScrollPane::ScrollPane(BasePretzel *base, int width, int height)
        : PretzelRow(base, width, height),
        mBotScrollPadding(10),
        bCanScroll(false),
        bHover(false),
        bDragging(false),
        mScrolledPct(0.0),
        mScrolledHandleAmt(0, 0),
        mScrolledFrameAmt(0, 0)
    {
        mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
    }
    
    void ScrollPane::updateChildrenBounds()
    {
        PretzelRow::updateChildrenBounds();
        
        // RESIZE CHILDREN
		vec2 newOffset(0, 0);
		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
			(*it)->updateBounds(newOffset, mBounds - Rectf(0,0,10,0));
			newOffset += vec2(0, (*it)->getHeight());
		}
        
        // HANDLE SCROLL BAR
        mChildrenHeight = newOffset.y;
        bCanScroll = (mBounds.getHeight() < mChildrenHeight) ? true : false;
        
        mScrollHandle.x1 = mBounds.x2-10;
        mScrollHandle.x2 = mBounds.x2;
        
        if( bCanScroll ){
            int rectMaxY = mBounds.y2 - mScrollHandle.getHeight() - mBotScrollPadding;
            mScrolledHandleAmt = vec2(0, rectMaxY*mScrolledPct);
            
            float scrollableHeight = mChildrenHeight - mBounds.getHeight() + 20; // to accomodate for bottom resize bar
            mScrolledFrameAmt = vec2( 0, scrollableHeight * -mScrolledPct );
            
            mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
            mScrollHandle.offset( mScrolledHandleAmt );
        }else{
            mScrolledPct = 0.0;
            mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
        }
        
        updateLabelPositions();
	}
    
    void ScrollPane::mouseDown(const ci::vec2 &pos)
    {
        if(bCanScroll){
            if( mScrollHandle.contains( pos ) ){
                bDragging = true;
                mStartDragOffset = mScrollHandle.getUpperLeft() - pos;
            }
        }
        
        PretzelRow::mouseDown( pos - mScrolledFrameAmt );
    }
    
    void ScrollPane::mouseDragged(const ci::vec2 &pos)
    {
        if( bDragging ){
            vec2 localPos = pos + mStartDragOffset;
            
            int rectMinY = 0;
            int rectMaxY = mBounds.y2 - mScrollHandle.getHeight() - mBotScrollPadding;
            
            mScrolledPct = ci::math<float>::clamp((float)(localPos.y - rectMinY) / (float)rectMaxY, 0.0, 1.0);
            mScrolledHandleAmt = vec2(0, rectMaxY*mScrolledPct);
            
            float scrollableHeight = mChildrenHeight - mBounds.getHeight() + 20; // to accomodate for bottom resize bar
            mScrolledFrameAmt = vec2( 0, scrollableHeight * -mScrolledPct );
            
            mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
            mScrollHandle.offset( mScrolledHandleAmt );
            
            updateLabelPositions();
        }else{
            PretzelRow::mouseDragged( pos - mScrolledFrameAmt );
        }
    }
    
    void ScrollPane::mouseUp(const ci::vec2 &pos)
    {
        bDragging = false;
        PretzelRow::mouseUp( pos - mScrolledFrameAmt );
    }
    
    void ScrollPane::mouseMoved(const ci::vec2 &pos)
    {
        if(bCanScroll){
            if( mScrollHandle.contains(pos) ){
                pretzel()->setCursor(CursorType::HAND);
                bHover = true;
            }else{
                if(bHover){
                    pretzel()->setCursor(CursorType::ARROW);
                }
                bHover = false;
            }
        }
        
        PretzelRow::mouseMoved( pos - mScrolledFrameAmt );
    }
    
    void ScrollPane::mouseWheel(const float increment)
    {
        PretzelRow::mouseWheel(increment);
        
        int rectMinY = 0;
        int rectMaxY = mBounds.y2 - mScrollHandle.getHeight() - mBotScrollPadding;
        
        float curY = math<float>::clamp(mScrollHandle.y1, rectMinY, rectMaxY);
        mScrolledPct = lmap(curY, (float)rectMinY, (float)rectMaxY, 0.0f, 1.0f);
        
        float scrollableHeight = mChildrenHeight - mBounds.getHeight() + 20; // to accomodate for bottom resize bar
        mScrolledFrameAmt = vec2( 0, scrollableHeight * -mScrolledPct );
        
        mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
        mScrollHandle.offset( vec2(0, glm::clamp(curY - increment, (float)rectMinY, (float)rectMaxY)) );
        
        updateLabelPositions();
    }
    
    void ScrollPane::updateLabelPositions()
    {
        for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
            if( (*it)->type == WidgetType::LABEL ){
                PretzelLabel *pl = (PretzelLabel*)(*it);
                if( -mScrolledFrameAmt.y > pl->getOffset().y ){
                    pl->scrollPaneOffset.y = -mScrolledFrameAmt.y - pl->getOffset().y;
                }else {
                    pl->scrollPaneOffset.y = 0;
                }
            }
        }
    }

    void ScrollPane::draw()
    {
        Rectf tBounds = getBounds();
        vec2 tPos = mOffset + mGlobalOffset;
        float winH = getWindowHeight();

        if ( ci::app::App::get()->isHighDensityDisplayEnabled()) {
            tBounds *= getWindowContentScale();
            winH *= getWindowContentScale();
            tPos *= getWindowContentScale();
        }
        
        gl::ScopedScissor scSc(tPos.x, winH - tBounds.y2 - tPos.y, tBounds.getWidth(), tBounds.getHeight());
        
        gl::color(pretzel()->P_BG_COLOR);
        gl::drawSolidRect( getBounds() );
        
        gl::translate(mOffset);
        
        if( getBounds().getHeight() < mChildrenHeight ){
            gl::pushMatrices();{
                gl::translate( mScrolledFrameAmt );
                PretzelRow::draw();
            }gl::popMatrices();
            
            if( bDragging ){
                gl::color( pretzel()->P_ACTIVE_COLOR );
            }else{
                gl::color( pretzel()->P_SLIDER_COLOR );
            }
            gl::drawSolidRect( mScrollHandle );
            
            gl::color( pretzel()->P_GUI_BORDER );
            gl::drawStrokedRect( mScrollHandle );
        }else{
            PretzelRow::draw();
        }
    }
}
