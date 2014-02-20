//
//  Header.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "BasePanel.h"

class PanelGui : public BasePanel {
  public:
    PanelGui();
    PanelGui( PanelFillStyle width, PanelFillStyle height );
    
    void update();
    void draw();
    void registerPanel( BasePanel *panel );
    
  private:
    void init();
    void updateChildrenBounds();
};