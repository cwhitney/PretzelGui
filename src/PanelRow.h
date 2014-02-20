//
//  PanelRow.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/Rand.h"
#include "BasePanel.h"

class PanelRow : public BasePanel {
  public:
    PanelRow( BasePanel *base, int width, int height );
    PanelRow( BasePanel *base, PanelFillStyle width, int height );
    PanelRow( BasePanel *base, int width, PanelFillStyle height );
    PanelRow( BasePanel *base, PanelFillStyle width, PanelFillStyle height );
    
    void draw();
    
    virtual void updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds );
    
  private:
    void initPanel( BasePanel *base, int width, int height );
    void updateChildrenBounds();
    
    ci::Color   mBgColor;
    bool        bFillWidth, bFillHeight;
};