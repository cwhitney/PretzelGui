#include "PretzelSaveLoad.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PretzelSaveLoad::PretzelSaveLoad(BasePretzel *parent) : BasePretzel() {
	mBounds.set(0, 0, 200, 23);
	parent->registerPretzel(this);
}

PretzelSaveLoad::PretzelSaveLoad(BasePretzel *parent, fs::path savePath) : BasePretzel() {
	parent->registerPretzel(this);
}

void PretzelSaveLoad::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds) {
	BasePretzel::updateBounds(offset, parentBounds);

	int margin = 10;
	int buttonWidth = (mBounds.getWidth() - margin * 3.0) * 0.5;
	int buttonHeight = 18;

	mSaveRect.set(margin, 0, buttonWidth + margin, buttonHeight);
	mLoadRect = mSaveRect.getOffset(Vec2f(buttonWidth + margin, 0));
}

void PretzelSaveLoad::mouseDown(const ci::Vec2i &pos){
	if (mSaveRect.contains(pos-mOffset)){
		console() << "Save!" << endl;
		mGlobal->saveSettings();
	}
	else if (mLoadRect.contains(pos-mOffset)){
		console() << "Load! " << endl;
		mGlobal->loadSettings();
	}
}

void PretzelSaveLoad::mouseDragged(const ci::Vec2i &pos){

}

void PretzelSaveLoad::mouseUp(const ci::Vec2i &pos){

}

void PretzelSaveLoad::draw() {
	gl::pushMatrices(); {
		gl::translate(mOffset + Vec2f(0,3));

		// SAVE
		gl::color(mGlobal->P_TAB_COLOR);
		gl::drawSolidRect(mSaveRect);

		gl::color(mGlobal->P_HIGHLIGHT_COLOR);
		gl::drawLine(mSaveRect.getUpperLeft() + Vec2f(0, 1), mSaveRect.getUpperRight() + Vec2f(0, 1));

		gl::color(mGlobal->P_OUTLINE_COLOR);
		gl::drawStrokedRect(mSaveRect);
		mGlobal->renderTextCentered("Save", Vec2f(mSaveRect.getCenter().x, 2));
		
		// LOAD
		gl::color(mGlobal->P_TAB_COLOR);
		gl::drawSolidRect(mLoadRect);

		gl::color(mGlobal->P_HIGHLIGHT_COLOR);
		gl::drawLine(mLoadRect.getUpperLeft() + Vec2f(0, 1), mLoadRect.getUpperRight() + Vec2f(0, 1));

		gl::color(mGlobal->P_OUTLINE_COLOR);
		gl::drawStrokedRect(mLoadRect);
		mGlobal->renderTextCentered("Load", Vec2f(mLoadRect.getCenter().x, 2));

	}gl::popMatrices();

}
