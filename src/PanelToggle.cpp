#include "PanelToggle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PanelToggle::PanelToggle(BasePanel *parent, std::string label, bool *value) : BasePanel() {
	mBounds.set(0, 0, 200, 23);
	mValue = value;
	mLabel = label;

	parent->registerPanel(this);
}


void PanelToggle::draw() {
	gl::pushMatrices(); {
		gl::translate(mOffset + Vec2f(5, 0));

		mGlobal->renderText(mLabel, Vec2i(24, 4));


		Rectf tmpRect = Rectf(0,0,mBounds.getHeight(), mBounds.getHeight());
		tmpRect.inflate( Vec2i(-5, -5));
		gl::color(mGlobal->P_SLIDER_COLOR);
		gl::drawSolidRect(tmpRect);

		tmpRect.inflate(Vec2i(-2, -2));
		if (*mValue){
			gl::color(mGlobal->P_SLIDER_COLOR);
		}else{
			gl::color(mGlobal->P_BG_COLOR);
		}
		
		gl::drawSolidRect(tmpRect);

	}gl::popMatrices();
}

void PanelToggle::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
	BasePanel::updateBounds(offset, parentBounds);

}

void PanelToggle::mouseDown(const ci::Vec2i &pos){
	if (mBounds.contains(pos - mOffset)){
		*mValue = !(*mValue);
		console() << "clicked! " << mValue << endl;
	}
}