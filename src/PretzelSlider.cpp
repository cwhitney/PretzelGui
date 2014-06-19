#include "PretzelSlider.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel{

    // =========================================================================================================================================
    PSlide::PSlide(){}
    void PSlide::setup(float *value, float min, float max, ci::Vec2f sliderLeft, ci::Vec2f sliderRight ){
        mValue = value;
        mMin = min;
        mMax = max;
        mSliderLeft = sliderLeft;
        mSliderRight = sliderRight;
    }

    // =========================================================================================================================================
    
	PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, int *value, int minVal, int maxVal) : BasePretzel(){
		mLabelText = labelText;

		mMin = minVal;
		mMax = maxVal;
		mValueInt = value;

        mHandHover = false;
		bUseInteger = true;
		bIsDragging = false;
		mBounds.set(0, 0, 200, 30);
		mHandlePos.set(15, 22);
		mHandleHitbox.set(-5, -7, 5, 5);
		mSliderPct = 0.0f;

		// slider boundaries
		mSliderLeft = mBounds.getUpperLeft() + Vec2f(10, 22);
		mSliderRight = mBounds.getUpperRight() + Vec2f(-10, 22);

		// texture skin rect
		mSkinTexRect.set(0, 0, 13, 12);
		mSkinDestRect = mSkinTexRect;
		mSkinDestRect.offset(Vec2i(-7, -7));
        
//        PSlide newSlider;
//        newSlider.setup(
        
		mGlobal->addSaveParam(labelText, value);

		parent->registerPretzel(this);
		updateValue(*mValueInt);
	}

	PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, float *value, float minVal, float maxVal) : BasePretzel(){
		mLabelText = labelText;

		mMin = minVal;
		mMax = maxVal;
		mValue = value;

		bUseInteger = false;
		bIsDragging = false;
        mHandHover = false;
		mBounds.set(0, 0, 200, 30);
		mHandlePos.set(15, 22);
		mHandleHitbox.set(-5, -7, 5, 5);
		mSliderPct = 0.0f;

		// slider boundaries
		mSliderLeft = mBounds.getUpperLeft() + Vec2f(10, 22);
		mSliderRight = mBounds.getUpperRight() + Vec2f(-10, 22);

		// texture skin rect
		mSkinTexRect.set(0, 0, 13, 12);
		mSkinDestRect = mSkinTexRect;
		mSkinDestRect.offset(Vec2i(-7, -7));

		mGlobal->addSaveParam(labelText, value);

		parent->registerPretzel(this);
		updateValue(*mValue);
	}

	void PretzelSlider::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
		BasePretzel::updateBounds(offset, parentBounds);

		mSliderLeft = mBounds.getUpperLeft() + Vec2f(10, 19);
		mSliderRight = mBounds.getUpperRight() + Vec2f(-10, 19);

		if (bUseInteger){
			updateValue(*mValueInt);
		}
		else{
			updateValue(*mValue);
		}
	}

	void PretzelSlider::updateValue(float val){
		if (mMin < mMax){
			val = math<float>::clamp(val, mMin, mMax);
		}
		else{
			val = math<float>::clamp(val, mMax, mMin);
		}
		if (bUseInteger){
			*mValueInt = floor(val);
		}
		else{
			*mValue = val;
		}
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

	void PretzelSlider::mouseMoved(const ci::Vec2i &pos){
        if (mBounds.contains(pos - mOffset)){
			Vec2f localCoord = pos - mOffset;
            
			if (mHandleHitbox.contains(localCoord - mHandlePos)){
                mHandHover = true;
				mGlobal->setCursor(CursorType::HAND);
			}else{
                if( mHandHover ){
                    mGlobal->setCursor(CursorType::ARROW);
                }
                mHandHover = false;
            }
		}else{
            if( mHandHover ){
                mGlobal->setCursor(CursorType::ARROW);
            }
            mHandHover = false;
        }
	}

	void PretzelSlider::mouseDragged(const Vec2i &pos){
		if (bIsDragging){
			mHandlePos.x = ci::math<float>::clamp(pos.x - mOffset.x, mSliderLeft.x, mSliderRight.x);
			mSliderPct = lmap<float>(mHandlePos.x, mSliderLeft.x, mSliderRight.x, 0.0, 1.0);

			if (bUseInteger){
				*mValueInt = floor((mMax - mMin) * mSliderPct + mMin);
			}
			else{
				*mValue = (mMax - mMin) * mSliderPct + mMin;
			}
		}
	}
	void PretzelSlider::mouseUp(const Vec2i &pos){
		bIsDragging = false;
	}

	void PretzelSlider::draw() {
		if (bUseInteger){
			updateValue(*mValueInt);
		}
		else{
			updateValue(*mValue);
		}

		gl::pushMatrices(); {
			gl::translate(mOffset);

			gl::pushMatrices(); {
				mGlobal->renderText(mLabelText, mBounds.getUpperLeft() + Vec2i(12, 1));
				if (bUseInteger){
					mGlobal->renderTextRight(to_string(*mValueInt), mBounds.getUpperRight() + Vec2i(-12, 1));
				}
				else{
					mGlobal->renderTextRight(mGlobal->to_string_with_precision(*mValue), mBounds.getUpperRight() + Vec2i(-12, 1));
				}
			}gl::popMatrices();

			gl::color(mGlobal->P_SLIDER_COLOR);
			gl::drawLine(mSliderLeft, mSliderRight);

			gl::color(ColorA(1, 1, 1, 1));
			gl::pushMatrices(); {
				gl::translate(mHandlePos);
				gl::draw(mGlobal->mSkinTex, mSkinTexRect, mSkinDestRect);
			}gl::popMatrices();
		}gl::popMatrices();
	}
    // =========================================================================================================================================
}