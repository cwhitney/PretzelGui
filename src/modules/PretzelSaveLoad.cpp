#include "PretzelSaveLoad.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel{
	PretzelSaveLoad::PretzelSaveLoad(BasePretzel *parent) : BasePretzel() {
		mBounds.set(0, 0, 200, 23);
		parent->registerPretzel(this);
		bHoverSave = false;
		bHoverLoad = false;
        
        mSaveBg = mGlobal->P_TAB_COLOR;
        mLoadBg = mGlobal->P_TAB_COLOR;
	}

	PretzelSaveLoad::PretzelSaveLoad(BasePretzel *parent, fs::path savePath) : BasePretzel() {
		parent->registerPretzel(this);
		bHoverSave = false;
		bHoverLoad = false;
	}

	void PretzelSaveLoad::updateBounds(const ci::vec2 &offset, const ci::RectT<float> &parentBounds) {
		BasePretzel::updateBounds(offset, parentBounds);

		int margin = 10;
		int buttonWidth = (mBounds.getWidth() - margin * 3.0) * 0.5;
		int buttonHeight = 18;

		mSaveRect.set(margin, 0, buttonWidth + margin, buttonHeight);
		mLoadRect = mSaveRect.getOffset(vec2(buttonWidth + margin, 0));
	}

	void PretzelSaveLoad::mouseDown(const ci::vec2 &pos){
		if (mSaveRect.contains(pos - mOffset)){
			mGlobal->saveSettings();
            mSaveBg.set( mGlobal->P_ACTIVE_COLOR );
		}
		else if (mLoadRect.contains(pos - mOffset)){
			mGlobal->loadSettings();
            mLoadBg.set( mGlobal->P_ACTIVE_COLOR );
		}
	}

	void PretzelSaveLoad::mouseMoved(const ci::vec2 &pos){
		if (mSaveRect.contains(pos - mOffset)){
			bHoverSave = true;
			bHoverLoad = false;
            mGlobal->setCursor( CursorType::HAND );
            mSaveBg.set( mGlobal->P_HOVER_COLOR );
            mLoadBg.set( mGlobal->P_TAB_COLOR );
		}
		else if (mLoadRect.contains(pos - mOffset)){
			bHoverSave = false;
			bHoverLoad = true;
            mGlobal->setCursor( CursorType::HAND );
            mLoadBg.set( mGlobal->P_HOVER_COLOR );
            mSaveBg.set( mGlobal->P_TAB_COLOR );
		}
		else{
            if( bHoverSave || bHoverLoad ){
                mGlobal->setCursor( CursorType::ARROW );
            }
            mSaveBg.set( mGlobal->P_TAB_COLOR );
            mLoadBg.set( mGlobal->P_TAB_COLOR );
			bHoverSave = false;
			bHoverLoad = false;
		}
	}
    
    void PretzelSaveLoad::mouseUp(const ci::vec2 &pos){
        mSaveBg.set( mGlobal->P_TAB_COLOR );
        mLoadBg.set( mGlobal->P_TAB_COLOR );
    }

	void PretzelSaveLoad::draw() {
		gl::pushMatrices(); {
			gl::translate(mOffset + vec2(0, 3));

			// SAVE
//			gl::color((bHoverSave) ? mGlobal->P_HOVER_COLOR : mGlobal->P_TAB_COLOR);
            gl::color( mSaveBg );
			gl::drawSolidRect(mSaveRect);

			gl::color(mGlobal->P_HIGHLIGHT_COLOR);
			gl::drawLine(mSaveRect.getUpperLeft() + vec2(0, 1), mSaveRect.getUpperRight() + vec2(0, 1));

			gl::color(mGlobal->P_OUTLINE_COLOR);
			gl::drawStrokedRect(mSaveRect);
			mGlobal->renderTextCentered("Save", vec2(mSaveRect.getCenter().x, 2));

			// LOAD
//			gl::color((bHoverLoad) ? mGlobal->P_HOVER_COLOR : mGlobal->P_TAB_COLOR);
            gl::color( mLoadBg );
			gl::drawSolidRect(mLoadRect);

			gl::color(mGlobal->P_HIGHLIGHT_COLOR);
			gl::drawLine(mLoadRect.getUpperLeft() + vec2(0, 1), mLoadRect.getUpperRight() + vec2(0, 1));

			gl::color(mGlobal->P_OUTLINE_COLOR);
			gl::drawStrokedRect(mLoadRect);
			mGlobal->renderTextCentered("Load", vec2(mLoadRect.getCenter().x, 2));

		}gl::popMatrices();
	}
}
