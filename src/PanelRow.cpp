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
    bFillWidth = false;
    bFillHeight = false;
    
    mBounds = Rectf(0, 0, width, height);
    base->registerPanel( this );
    
    mBgColor = Color( Rand::randFloat(1.0), Rand::randFloat(1.0), Rand::randFloat(1.0) );
}

// ---------------------------------------------------------------
void BasePanel::updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds ){
    mOffset.set( offset );
    mParentBounds = parentBounds;
}

void PanelRow::updateChildrenBounds() {
    float newWidth  = mBounds.getWidth();
    float newHeight = mBounds.getHeight();
    
    if( bFillWidth ){
        newWidth = mParentBounds.getWidth();
    }
    
    if( bFillHeight ){
        newHeight = mParentBounds.getHeight();
    }
}

// ---------------------------------------------------------------
void PanelRow::draw(){
    gl::color( mBgColor );
    gl::drawSolidRect( mBounds );
}