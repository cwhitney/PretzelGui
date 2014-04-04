#include "PanelButton.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PanelButton::PanelButton(BasePanel *parent, string labelText) : BasePanel() {
	mBounds.set(0, 0, 200, 23);
	mButtonBounds = mBounds;
	mButtonBounds.inflate(Vec2f(-5, -3));

	mLabelText = labelText;
	parent->registerPanel(this);
}

void PanelButton::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds) {
	BasePanel::updateBounds(offset, parentBounds);

	mButtonBounds = mBounds;
	mButtonBounds.inflate(Vec2f(-10, -1));
}

void PanelButton::mouseDown(const ci::Vec2i &pos){
	if (mBounds.contains(pos-mOffset)){
		signalOnPress();
	}
}

void PanelButton::draw(){
	gl::pushMatrices(); {
		gl::translate(mOffset);
		gl::color(mGlobal->P_TAB_COLOR);
		gl::drawSolidRect(mButtonBounds);

		gl::color(mGlobal->P_HIGHLIGHT_COLOR);
		gl::drawLine(mButtonBounds.getUpperLeft() + Vec2f(0, 1), mButtonBounds.getUpperRight() + Vec2f(0, 1));

		gl::color(mGlobal->P_OUTLINE_COLOR);
		gl::drawStrokedRect(mButtonBounds);
		mGlobal->renderTextCentered(mLabelText, Vec2f(mButtonBounds.getCenter().x, 2));
	}gl::popMatrices();
}