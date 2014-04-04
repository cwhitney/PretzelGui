//
//  BasePanel.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include <boost/algorithm/string.hpp>
#include "PanelGlobal.h"

enum PanelFillStyle {
    FILL = 0
};

class BasePanel {
  public:
    BasePanel();
  
    virtual void draw(){};
	virtual void registerPanel(BasePanel *panel);
    
    virtual void updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds );
    
    virtual ci::Rectf getBounds();
    virtual float getWidth();
    virtual float getHeight();

	virtual void mouseDown(const ci::Vec2i &pos);
	virtual void mouseDragged(const ci::Vec2i &pos);
	virtual void mouseUp(const ci::Vec2i &pos);
    
  protected:
    virtual void updateChildrenBounds();

	ci::Vec2f                   mOffset;
	ci::Rectf                   mBounds;

	std::vector<BasePanel*>     mPanelChildren;
    ci::Rectf                   mParentBounds;

	Panel::PanelGlobal			*mGlobal;
};