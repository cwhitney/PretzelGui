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

namespace Pretzel {

    ScrollPane::ScrollPane(BasePretzel *base, int width, int height) : PretzelRow(base, width, height) {
        bCanScroll = false;
        bHover = false;
		bDragging = false;
        mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
        mScrolledPct = 0.0;
        mScrolledHandleAmt.set(0,0);
        mScrolledFrameAmt.set(0,0);
    }
    
    void ScrollPane::updateChildrenBounds() {
        PretzelRow::updateChildrenBounds();
        
        // RESIZE CHILDREN
		Vec2f newOffset(0, 0);
		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
			(*it)->updateBounds(newOffset, mBounds - Rectf(0,0,10,0));
			newOffset += Vec2f(0, (*it)->getHeight());
		}
        
        // HANDLE SCROLL BAR
        mChildrenHeight = newOffset.y;
        bCanScroll = (mBounds.getHeight() < mChildrenHeight) ? true : false;
        
        mScrollHandle.x1 = mBounds.x2-10;
        mScrollHandle.x2 = mBounds.x2;
        
        if( bCanScroll ){
            int rectMaxY = mBounds.y2 - mScrollHandle.getHeight() - 10; // -10 for bottom bar
            mScrolledHandleAmt.set(0, rectMaxY*mScrolledPct);
            
            float scrollableHeight = mChildrenHeight - mBounds.getHeight() + 20; // to accomodate for bottom resize bar
            mScrolledFrameAmt.set( 0, scrollableHeight * -mScrolledPct );
            
            mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
            mScrollHandle.offset( mScrolledHandleAmt );
        }else{
            mScrolledPct = 0.0;
            mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
        }
	}
    
    void ScrollPane::mouseDown(const ci::Vec2i &pos){
        if(bCanScroll){
            if( mScrollHandle.contains( pos ) ){
                bDragging = true;
                mStartDragOffset = mScrollHandle.getUpperLeft() - pos;
            }
        }
        
        PretzelRow::mouseDown( pos - mScrolledFrameAmt );
    }
    
    void ScrollPane::mouseDragged(const ci::Vec2i &pos){
        if( bDragging ){
            Vec2i localPos = pos + mStartDragOffset;
            
            int rectMinY = 0;
            int rectMaxY = mBounds.y2 - mScrollHandle.getHeight() - 10; // -10 for bottom bar
            
            mScrolledPct = ci::math<float>::clamp((float)(localPos.y - rectMinY) / (float)rectMaxY, 0.0, 1.0);
            mScrolledHandleAmt.set(0, rectMaxY*mScrolledPct);
            
            float scrollableHeight = mChildrenHeight - mBounds.getHeight() + 20; // to accomodate for bottom resize bar
            mScrolledFrameAmt.set( 0, scrollableHeight * -mScrolledPct );
            
            mScrollHandle = Rectf(mBounds.x2-10, 0, mBounds.x2, 50);
            mScrollHandle.offset( mScrolledHandleAmt );
        }else{
            PretzelRow::mouseDragged( pos - mScrolledFrameAmt );
        }
    }
    
    void ScrollPane::mouseUp(const ci::Vec2i &pos){
        bDragging = false;
        PretzelRow::mouseUp( pos - mScrolledFrameAmt );
    }
    
    void ScrollPane::mouseMoved(const ci::Vec2i &pos){
        if(bCanScroll){
            if( mScrollHandle.contains(pos) ){
                mGlobal->setCursor(CursorType::HAND);
                bHover = true;
            }else{
                if(bHover){
                    mGlobal->setCursor(CursorType::ARROW);
                }
                bHover = false;
            }
        }
        
        PretzelRow::mouseMoved( pos - mScrolledFrameAmt );
    }

    void ScrollPane::draw(){
        glEnable(GL_SCISSOR_TEST);
        Rectf tBounds = mBounds;
        Vec2f tPos = mOffset + mGlobalOffset;
        float winH = getWindowHeight();

        if( ci::app::App::get()->getSettings().isHighDensityDisplayEnabled() ){
            tBounds *= getWindowContentScale();
            winH *= getWindowContentScale();
            tPos *= getWindowContentScale();
        }

        glScissor( tPos.x, winH - tBounds.y2 - tPos.y, tBounds.getWidth(), tBounds.getHeight());
        
        gl::color(mGlobal->P_BG_COLOR);
        gl::drawSolidRect( mBounds );
        
        gl::translate(mOffset);
        
        if( mBounds.getHeight() < mChildrenHeight ){
            gl::pushMatrices();{
                gl::translate( mScrolledFrameAmt );
                PretzelRow::draw();
            }gl::popMatrices();
            
            if( bDragging ){
                gl::color( mGlobal->P_ACTIVE_COLOR );
            }else{
                gl::color( mGlobal->P_SLIDER_COLOR );
            }
            gl::drawSolidRect( mScrollHandle );
            
            gl::color( mGlobal->P_GUI_BORDER );
            gl::drawStrokedRect( mScrollHandle );
        }else{
            PretzelRow::draw();
        }
        
        glDisable(GL_SCISSOR_TEST);
    }
}