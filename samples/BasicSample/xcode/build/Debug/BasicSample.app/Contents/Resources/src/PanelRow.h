//
//  PanelRow.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "BasePanel.h"

class PanelRow : public BasePanel {
  public:
    PanelRow( BasePanel *base, int width, int height );
    void draw();
    
  protected:
    ci::Rectf           mBounds;
    
};