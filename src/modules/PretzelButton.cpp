#include "PretzelButton.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel
{
	PretzelButton::PretzelButton(BasePretzel *parent, string labelText) : BasePretzel() {
		mBounds.set(0, 0, 200, 26);
		mButtonBounds = mBounds;
		mButtonBounds.inflate(vec2(-10, -3));
		mButtonBounds.y2--;

		bHover = false;
		mLabelText = labelText;
		parent->registerPretzel(this);
        
        mBgColor = mGlobal->P_TAB_COLOR;
        
        type = WidgetType::BUTTON;
	}

	void PretzelButton::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) {
		BasePretzel::updateBounds(offset, parentBounds);

		mButtonBounds = mBounds;
		mButtonBounds.inflate(vec2(-10, -3));
		mButtonBounds.y2 -= 1;
	}

	void PretzelButton::mouseDown(const ci::vec2 &pos){
		if (mBounds.contains(pos - mOffset)){
            mBgColor = mGlobal->P_ACTIVE_COLOR;
			signalOnPress.emit();
		}
	}
    
    void PretzelButton::mouseUp(const ci::vec2 &pos){
		mBgColor = mGlobal->P_TAB_COLOR;
	}

	void PretzelButton::mouseMoved(const ci::vec2 &pos){
		if (mBounds.contains(pos - mOffset)){
			bHover = true;
            mBgColor = mGlobal->P_HOVER_COLOR;
            mGlobal->setCursor( CursorType::HAND );
		}
		else{
            if( bHover ){
                mGlobal->setCursor( CursorType::ARROW );
                mBgColor = mGlobal->P_TAB_COLOR;
            }
			bHover = false;
		}
	}

	void PretzelButton::draw(){
		gl::pushMatrices(); {
			gl::translate(mOffset);
            gl::color( mBgColor );
            PWindow()->drawSolidRect( mButtonBounds );

			gl::color(mGlobal->P_HIGHLIGHT_COLOR);
			PWindow()->drawLine(mButtonBounds.getUpperLeft() + vec2(0, 1), mButtonBounds.getUpperRight() + vec2(0, 1));

			gl::color(mGlobal->P_OUTLINE_COLOR);
			PWindow()->drawStrokedRect(mButtonBounds);
			mGlobal->renderTextCentered(mLabelText, vec2(mButtonBounds.getCenter().x, 5));
		}gl::popMatrices();
	}
}
