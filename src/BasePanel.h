//
//  BasePanel.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

enum PanelFillStyle {
    FILL = 0
};

class BasePanel {
  public:
    BasePanel();
  
    virtual void draw(){};
    virtual void registerPanel( BasePanel *panel ){};
    
    virtual void updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds );
    
    virtual float getWidth();
    virtual float getHeight();
    
  protected:
    virtual void updateChildrenBounds();
    
    std::vector<BasePanel*>     mPanelChildren;
    ci::Vec2f                   mOffset;
    ci::Rectf                   mParentBounds;
    ci::Rectf                   mBounds;
};