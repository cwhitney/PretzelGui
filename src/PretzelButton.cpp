#include "PretzelButton.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PretzelButton::PretzelButton(BasePretzel *parent, string labelText) : BasePretzel() {
	mBounds.set(0, 0, 200, 22);
	mButtonBounds = mBounds;
	mButtonBounds.inflate(Vec2f(-10, -1));
	mButtonBounds.y2--;

	bHover = false;
	mLabelText = labelText;
	parent->registerPretzel(this);
}

void PretzelButton::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds) {
	BasePretzel::updateBounds(offset, parentBounds);

	mButtonBounds = mBounds;
	mButtonBounds.inflate(Vec2f(-10, -1));
	mButtonBounds.y2 -= 1;
}

void PretzelButton::mouseDown(const ci::Vec2i &pos){
	if (mBounds.contains(pos-mOffset)){
		signalOnPress();
	}
}

void PretzelButton::mouseMoved(const ci::Vec2i &pos){
	if (mBounds.contains(pos - mOffset)){
		bHover = true;
	}else{
		bHover = false;
	}
}

void PretzelButton::draw(){
	gl::pushMatrices(); {
		gl::translate(mOffset);
		if (bHover){
			gl::color(mGlobal->P_HOVER_COLOR);
		}else{
			gl::color(mGlobal->P_TAB_COLOR);
		}
		gl::drawSolidRect(mButtonBounds);

		gl::color(mGlobal->P_HIGHLIGHT_COLOR);
		gl::drawLine(mButtonBounds.getUpperLeft() + Vec2f(0, 1), mButtonBounds.getUpperRight() + Vec2f(0, 1));

		gl::color(mGlobal->P_OUTLINE_COLOR);
		gl::drawStrokedRect(mButtonBounds);
		mGlobal->renderTextCentered(mLabelText, Vec2f(mButtonBounds.getCenter().x, 3));
	}gl::popMatrices();
}