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
using namespace Pretzel;

PretzelRow::PretzelRow( BasePretzel *base, int width, int height ) : BasePretzel() {
    initPretzel(base, width, height);
}

PretzelRow::PretzelRow( BasePretzel *base, PretzelFillStyle width, int height ) {
    initPretzel( base, getWindowWidth(), height );
    bFillWidth = true;
}

PretzelRow::PretzelRow( BasePretzel *base, int width, PretzelFillStyle height ) {
    initPretzel( base, width, getWindowHeight() );
    bFillHeight = true;
}

PretzelRow::PretzelRow( BasePretzel *base, PretzelFillStyle width, PretzelFillStyle height ) {
    initPretzel( base, getWindowWidth(), getWindowHeight() );
    bFillWidth = true;
    bFillHeight = true;
}

void PretzelRow::initPretzel(BasePretzel *base, int width, int height) {
    bFillWidth = false;
    bFillHeight = false;
    
    mBounds = Rectf(0, 0, width, height);

	if (base != NULL){	// if it's not a root node, ie. the base PretzelGui
		base->registerPretzel(this);
	}

//    mBgColor = Color( Rand::randFloat(1.0), Rand::randFloat(1.0), Rand::randFloat(1.0) );
}

// ---------------------------------------------------------------
void PretzelRow::updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds ){
    mOffset.set( offset );
    mParentBounds = parentBounds;
}

void PretzelRow::updateChildrenBounds() {
	Vec2f newOffset(0, 0);

	for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
		(*it)->updateBounds(newOffset, mBounds);
		newOffset += Vec2f(0, (*it)->getHeight());
	}
}

// ---------------------------------------------------------------
void PretzelRow::draw(){
	gl::color(mGlobal->P_BG_COLOR);
    gl::drawSolidRect( mBounds );
    
	for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
		(*it)->draw();
	}
}