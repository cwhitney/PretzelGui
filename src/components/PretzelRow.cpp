//
//  PretzelRow.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "PretzelRow.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel{
	PretzelRow::PretzelRow(BasePretzel *base, int width, int height) : BasePretzel() {
		initPretzel(base, width, height);
	}

	void PretzelRow::initPretzel(BasePretzel *base, int width, int height) {
		bFillWidth = false;
		bFillHeight = false;

		mBounds = Rectf(0, 0, width, height);

		if (base != NULL){	// if it's not a root node, ie. the base PretzelGui
			base->registerPretzel(this);
		}
	}

    // ---------------------------------------------------------------
	void PretzelRow::updateChildrenBounds() {
        BasePretzel::updateChildrenBounds();
        
		vec2 newOffset(0, 0);

		for (vector<BasePretzel*>::const_iterator it=mPretzelChildren.begin(); it!=mPretzelChildren.end(); ++it){
			(*it)->updateBounds(newOffset, mBounds);
			newOffset += vec2(0, (*it)->getHeight());
		}
	}

	// ---------------------------------------------------------------
	void PretzelRow::draw(){
		gl::color(mGlobal->P_BG_COLOR);
		gl::drawSolidRect(mBounds);

		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
			(*it)->draw();
		}
	}
}