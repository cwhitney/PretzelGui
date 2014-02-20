//
//  Header.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "PanelGui.h"

using namespace ci;
using namespace std;

PanelGui::PanelGui() : BasePanel() {
    init();
    mBounds.set( 0, 0, app::getWindowWidth(), app::getWindowHeight() );
}

PanelGui::PanelGui( PanelFillStyle width, PanelFillStyle height ) : BasePanel() {
    init();
    mBounds.set( 0, 0, app::getWindowWidth(), app::getWindowHeight() );
}

void PanelGui::init(){
}

// ---------------------------------------------------------
void PanelGui::update() {
    mBounds.set( 0, 0, app::getWindowWidth(), app::getWindowHeight() );
    updateChildrenBounds();
}

void PanelGui::draw(){
    for( vector<BasePanel*>::const_iterator it=mPanelChildren.begin(); it!=mPanelChildren.end(); it++ ){
        (*it)->draw();
    }
}

// ---------------------------------------------------------
void PanelGui::registerPanel( BasePanel *panel ) {
    mPanelChildren.push_back( panel );
    
    updateChildrenBounds();
}

void PanelGui::updateChildrenBounds() {
    // Just iterate through rows and set the sizes
    
    float rowHeightOffset = 0;
    
    for( vector<BasePanel*>::const_iterator it=mPanelChildren.begin(); it!=mPanelChildren.end(); it++ ){
        (*it)->updateBounds( Vec2f(0,rowHeightOffset), mBounds );
        
        rowHeightOffset += (*it)->getHeight();
    }
    
}