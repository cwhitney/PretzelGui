//
//  BasePretzel.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "BasePretzel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

BasePretzel::BasePretzel() {
    mOffset.set(0,0);
    mBounds.set(0,0,0,0);

	mGlobal = Pretzel::PretzelGlobal::getInstance();
}

void BasePretzel::registerPretzel(BasePretzel *Pretzel){
	mPretzelChildren.push_back(Pretzel);
	updateChildrenBounds();
}

// -------------------------------------------------------
void BasePretzel::updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds ){
    mOffset.set( offset );
    mParentBounds = parentBounds;

	mBounds.x2 = parentBounds.getWidth();
}

// -------------------------------------------------------------
ci::Rectf BasePretzel::getBounds() {
    return mBounds;
}

float BasePretzel::getWidth() {
    return mBounds.getWidth();
}

float BasePretzel::getHeight() {
    return mBounds.getHeight();
}

void BasePretzel::updateChildrenBounds() {
	
}

// -------------------------------------------------------------------
void BasePretzel::mouseDown(const ci::Vec2i &pos){
	for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
		(*it)->mouseDown(pos);
	}
}
void BasePretzel::mouseDragged(const ci::Vec2i &pos){
	for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
		(*it)->mouseDragged(pos);
	}
}
void BasePretzel::mouseUp(const ci::Vec2i &pos){
	for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
		(*it)->mouseUp(pos);
	}
}