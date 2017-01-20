#include "PretzelToggle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel{
	PretzelToggle::PretzelToggle(BasePretzel *parent, std::string label, bool *value) : BasePretzel() {
		mBounds.set(0, 0, 200, 23);
        bHover = false;
		mValue = value;
		mLabel = label;
        type = WidgetType::TOGGLE;

		int size = 11;
		mCheckBoxRect.set(0, 0, size, size);
		mCheckBoxRect.offset(vec2(11, 3));

		// texture skin rect
		mSkinTexRect.set(14, 0, 27, 11);
		mSkinDestRect.set(0, 0, mSkinTexRect.getWidth(), mSkinTexRect.getHeight());
		mSkinDestRect.offset(vec2(12, 2));

		mGlobal->addSaveParam(label, value);

		parent->registerPretzel(this);
	}

	void PretzelToggle::draw() {
		gl::pushMatrices(); {
			gl::translate(mOffset + vec2(0,2));

			// draw box
			RectT<float> tmpRect = mCheckBoxRect;

			gl::color(mGlobal->P_SLIDER_COLOR);
			PWindow()->drawSolidRect(tmpRect);

			tmpRect.inflate(vec2(-2, -2));
			gl::color(mGlobal->P_BG_COLOR);
			PWindow()->drawSolidRect(tmpRect);

			// draw check
			if(*mValue){
				gl::color(ColorA(1, 1, 1, 1));
				gl::draw(mGlobal->mSkinTex, mSkinTexRect, mSkinDestRect);
			}
			mGlobal->renderText(mLabel, vec2(27, 1));

		}gl::popMatrices();
	}

	void PretzelToggle::updateBounds(const ci::vec2 &offset, const ci::RectT<float> &parentBounds){
		BasePretzel::updateBounds(offset, parentBounds);
	}

    void PretzelToggle::mouseMoved(const ci::vec2 &pos){
        if (mSkinDestRect.contains(pos - mOffset)){
            bHover = true;
            mGlobal->setCursor(CursorType::HAND);
        }else{
            if(bHover){
                mGlobal->setCursor(CursorType::ARROW);
            }
            bHover = false;
        }
    }
    
	void PretzelToggle::mouseDown(const ci::vec2 &pos){
		if (mBounds.contains(pos - mOffset)){
			*mValue = !(*mValue);
		}
	}
}
