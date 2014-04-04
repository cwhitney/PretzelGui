//
//  BasePanel.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "BasePanel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

BasePanel::BasePanel() {
    mOffset.set(0,0);
    mBounds.set(0,0,0,0);

	mGlobal = Panel::PanelGlobal::getInstance();
}

void BasePanel::registerPanel(BasePanel *panel){
	mPanelChildren.push_back(panel);
	updateChildrenBounds();
}

// -------------------------------------------------------
void BasePanel::updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds ){
    mOffset.set( offset );
    mParentBounds = parentBounds;

	mBounds.x2 = parentBounds.getWidth();
}

// -------------------------------------------------------------
ci::Rectf BasePanel::getBounds() {
    return mBounds;
}

float BasePanel::getWidth() {
    return mBounds.getWidth();
}

float BasePanel::getHeight() {
    return mBounds.getHeight();
}

void BasePanel::updateChildrenBounds() {
	
}

// -------------------------------------------------------------------
void BasePanel::mouseDown(const ci::Vec2i &pos){
	for (vector<BasePanel*>::const_iterator it = mPanelChildren.begin(); it != mPanelChildren.end(); ++it){
		(*it)->mouseDown(pos);
	}
}
void BasePanel::mouseDragged(const ci::Vec2i &pos){
	for (vector<BasePanel*>::const_iterator it = mPanelChildren.begin(); it != mPanelChildren.end(); ++it){
		(*it)->mouseDragged(pos);
	}
}
void BasePanel::mouseUp(const ci::Vec2i &pos){
	for (vector<BasePanel*>::const_iterator it = mPanelChildren.begin(); it != mPanelChildren.end(); ++it){
		(*it)->mouseUp(pos);
	}
}