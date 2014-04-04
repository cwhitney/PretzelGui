//
//  PanelRow.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "PanelRow.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace Panel;

PanelRow::PanelRow( BasePanel *base, int width, int height ) : BasePanel() {
    initPanel(base, width, height);
}

PanelRow::PanelRow( BasePanel *base, PanelFillStyle width, int height ) {
    initPanel( base, getWindowWidth(), height );
    bFillWidth = true;
}

PanelRow::PanelRow( BasePanel *base, int width, PanelFillStyle height ) {
    initPanel( base, width, getWindowHeight() );
    bFillHeight = true;
}

PanelRow::PanelRow( BasePanel *base, PanelFillStyle width, PanelFillStyle height ) {
    initPanel( base, getWindowWidth(), getWindowHeight() );
    bFillWidth = true;
    bFillHeight = true;
}

void PanelRow::initPanel(BasePanel *base, int width, int height) {
    
    console() << "INIT PANEL" << std::endl;
    bFillWidth = false;
    bFillHeight = false;
    
    mBounds = Rectf(0, 0, width, height);

	if (base != NULL){	// if it's not a root node, ie. the base PanelGui
		base->registerPanel(this);
	}

//    mBgColor = Color( Rand::randFloat(1.0), Rand::randFloat(1.0), Rand::randFloat(1.0) );
}

// ---------------------------------------------------------------
void PanelRow::updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds ){
    mOffset.set( offset );
    mParentBounds = parentBounds;
}

void PanelRow::updateChildrenBounds() {
	ci::app::console() << "update" << endl;

	Vec2f newOffset(0, 0);

	for (vector<BasePanel*>::const_iterator it = mPanelChildren.begin(); it != mPanelChildren.end(); ++it){
		(*it)->updateBounds(newOffset, mBounds);
		newOffset += Vec2f(0, (*it)->getHeight());
	}
}

// ---------------------------------------------------------------
void PanelRow::draw(){
	gl::color(mGlobal->P_BG_COLOR);
    gl::drawSolidRect( mBounds );
    
	for (vector<BasePanel*>::const_iterator it = mPanelChildren.begin(); it != mPanelChildren.end(); ++it){
		(*it)->draw();
	}
}