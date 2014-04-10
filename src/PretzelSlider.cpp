#include "PretzelSlider.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, float *value, float minVal, float maxVal) : BasePretzel(){
	mLabelText = labelText;
	//boost::to_upper(mLabelText);
	mMin = minVal;
	mMax = maxVal;
	mValue = value;

	bIsDragging = false;
	mBounds.set(0, 0, 200, 30);
	mHandlePos.set(15, 22);
	mHandleHitbox.set(-5, -5, 5, 5);
	mSliderPct = 0.0f;

	// slider boundaries
	mSliderLeft = mBounds.getUpperLeft() + Vec2f(10, 22);
	mSliderRight = mBounds.getUpperRight() + Vec2f(-10, 22);

	// texture skin rect
	mSkinTexRect.set(0, 0, 13, 12);
	mSkinDestRect = mSkinTexRect;
	mSkinDestRect.offset(Vec2i(-7,-6));

	parent->registerPretzel(this);

	mGlobal = Pretzel::PretzelGlobal::getInstance();

	updateValue(*mValue);
}

void PretzelSlider::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
	BasePretzel::updateBounds(offset, parentBounds);

	mSliderLeft = mBounds.getUpperLeft() + Vec2f(10, 19);
	mSliderRight = mBounds.getUpperRight() + Vec2f(-10, 19);

	updateValue(*mValue);
}

void PretzelSlider::updateValue(float val){
	if (mMin < mMax){
		val = math<float>::clamp(val, mMin, mMax);
	}else{
		val = math<float>::clamp(val, mMax, mMin);
	}
	*mValue = val;

	mSliderPct = (val - mMin) / (mMax - mMin);
	mHandlePos.x = lerp(mSliderLeft.x, mSliderRight.x, mSliderPct);
}

void PretzelSlider::mouseDown(const Vec2i &pos){
	if (mBounds.contains(pos - mOffset)){

		Vec2f localCoord = pos - mOffset;

		if (mHandleHitbox.contains(localCoord - mHandlePos)){
			bIsDragging = true;
			mHandlePos.x = pos.x - mOffset.x;
		}
	}
}

void PretzelSlider::mouseDragged(const Vec2i &pos){
	if (bIsDragging){
		mHandlePos.x = ci::math<float>::clamp(pos.x - mOffset.x, mSliderLeft.x, mSliderRight.x);
		mSliderPct = lmap<float>(mHandlePos.x, mSliderLeft.x, mSliderRight.x, 0.0, 1.0);

		*mValue = (mMax - mMin) * mSliderPct + mMin;
	}
}
void PretzelSlider::mouseUp(const Vec2i &pos){
	bIsDragging = false;
}

void PretzelSlider::draw() {
	gl::pushMatrices(); {
		gl::translate(mOffset);

		gl::pushMatrices(); {
			mGlobal->renderText(mLabelText, mBounds.getUpperLeft() + Vec2i(12,1));
			mGlobal->renderTextRight(mGlobal->to_string_with_precision(*mValue), mBounds.getUpperRight() + Vec2i(-12, 1) );
		}gl::popMatrices();

		gl::color(mGlobal->P_SLIDER_COLOR);
		gl::drawLine(mSliderLeft, mSliderRight);

		gl::color(ColorA(1,1,1,1));
		gl::pushMatrices(); {
			gl::translate(mHandlePos);
			gl::draw(mGlobal->mSkinTex, mSkinTexRect, mSkinDestRect);
		}gl::popMatrices();
	}gl::popMatrices();
}
