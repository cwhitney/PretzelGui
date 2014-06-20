#include "PretzelButton.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel{
	PretzelButton::PretzelButton(BasePretzel *parent, string labelText) : BasePretzel() {
		mBounds.set(0, 0, 200, 26);
		mButtonBounds = mBounds;
		mButtonBounds.inflate(Vec2f(-10, -3));
		mButtonBounds.y2--;

		bHover = false;
		mLabelText = labelText;
		parent->registerPretzel(this);
        
        mBgColor.set( mGlobal->P_TAB_COLOR );
        
        type = WidgetType::BUTTON;
	}

	void PretzelButton::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds) {
		BasePretzel::updateBounds(offset, parentBounds);

		mButtonBounds = mBounds;
		mButtonBounds.inflate(Vec2f(-10, -3));
		mButtonBounds.y2 -= 1;
	}

	void PretzelButton::mouseDown(const ci::Vec2i &pos){
		if (mBounds.contains(pos - mOffset)){
            mBgColor.set( mGlobal->P_ACTIVE_COLOR );
			signalOnPress();
		}
	}
    
    void PretzelButton::mouseUp(const ci::Vec2i &pos){
		mBgColor.set( mGlobal->P_TAB_COLOR );
	}

	void PretzelButton::mouseMoved(const ci::Vec2i &pos){
		if (mBounds.contains(pos - mOffset)){
			bHover = true;
            mBgColor.set( mGlobal->P_HOVER_COLOR );
            mGlobal->setCursor( CursorType::HAND );
		}
		else{
            if( bHover ){
                mGlobal->setCursor( CursorType::ARROW );
                mBgColor.set( mGlobal->P_TAB_COLOR );
            }
			bHover = false;
		}
	}

	void PretzelButton::draw(){
		gl::pushMatrices(); {
			gl::translate(mOffset);
//			if (bHover){
//				gl::color(mGlobal->P_HOVER_COLOR);
//			}
//			else{
//				gl::color(mGlobal->P_TAB_COLOR);
                gl::color( mBgColor );
//			}
			gl::drawSolidRect(mButtonBounds);

			gl::color(mGlobal->P_HIGHLIGHT_COLOR);
			gl::drawLine(mButtonBounds.getUpperLeft() + Vec2f(0, 1), mButtonBounds.getUpperRight() + Vec2f(0, 1));

			gl::color(mGlobal->P_OUTLINE_COLOR);
			gl::drawStrokedRect(mButtonBounds);
			mGlobal->renderTextCentered(mLabelText, Vec2f(mButtonBounds.getCenter().x, 5));
		}gl::popMatrices();
	}
}