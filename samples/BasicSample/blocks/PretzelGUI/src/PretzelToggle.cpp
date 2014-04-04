#include "PretzelToggle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PretzelToggle::PretzelToggle(BasePretzel *parent, std::string label, bool *value) : BasePretzel() {
	mBounds.set(0, 0, 200, 23);
	mValue = value;
	mLabel = label;

	parent->registerPretzel(this);
}


void PretzelToggle::draw() {
	gl::pushMatrices(); {
		gl::translate(mOffset + Vec2f(6, 0));

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

void PretzelToggle::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
	BasePretzel::updateBounds(offset, parentBounds);

}

void PretzelToggle::mouseDown(const ci::Vec2i &pos){
	if (mBounds.contains(pos - mOffset)){
		*mValue = !(*mValue);
	}
}