//
//  PretzelColorPicker.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 6/30/14.
//
//

#include "PretzelColorPicker.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel{
	PretzelColorPicker::PretzelColorPicker(BasePretzel *parent, std::string label, ci::Color *value) : BasePretzel() {
		mBounds.set(0, 0, 200, 23);
//        bHover = false;
//		mValue = value;
//		mLabel = label;
//        
//		int size = 11;
//		mCheckBoxRect.set(0, 0, size, size);
//		mCheckBoxRect.offset(Vec2i(11, 3));
//        
//		// texture skin rect
//		mSkinTexRect.set(14, 0, 27, 11);
//		mSkinDestRect.set(0, 0, mSkinTexRect.getWidth(), mSkinTexRect.getHeight());
//		mSkinDestRect.offset(Vec2i(12, 2));
//        
//		mGlobal->addSaveParam(label, value);
        
		parent->registerPretzel(this);
	}
    
	void PretzelColorPicker::draw() {
//		gl::pushMatrices(); {
//			gl::translate(mOffset + Vec2i(0,2));
//            
//			// draw box
//			Rectf tmpRect = mCheckBoxRect;
//            
//			gl::color(mGlobal->P_SLIDER_COLOR);
//			gl::drawSolidRect(tmpRect);
//            
//			tmpRect.inflate(Vec2i(-2, -2));
//			gl::color(mGlobal->P_BG_COLOR);
//			gl::drawSolidRect(tmpRect);
//            
//			// draw check
//			if(*mValue){
//				gl::color(ColorA(1, 1, 1, 1));
//				gl::draw(mGlobal->mSkinTex, mSkinTexRect, mSkinDestRect);
//			}
//			mGlobal->renderText(mLabel, Vec2i(27, 1));
//            
//		}gl::popMatrices();
	}
}