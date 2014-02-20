//
//  BasePanel.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "BasePanel.h"

using namespace ci;
using namespace std;

BasePanel::BasePanel() {
    mOffset.set(0,0);
    mBounds.set(0,0,0,0);
}

void BasePanel::updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds ){
    mOffset.set( offset );
    mParentBounds = parentBounds;
}

float BasePanel::getWidth() {
    return mBounds.getWidth();
}

float BasePanel::getHeight() {
    return mBounds.getHeight();
}

void BasePanel::updateChildrenBounds() {
    
}