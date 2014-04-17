//
//  BasePretzel.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include <boost/algorithm/string.hpp>
#include "PretzelGlobal.h"

enum PretzelFillStyle {
    FILL = 0
};

class BasePretzel {
  public:
    BasePretzel();
  
    virtual void draw(){};
	virtual void registerPretzel(BasePretzel *Pretzel);
    
    virtual void updateBounds( const ci::Vec2f &offset, const ci::Rectf &parentBounds );
    
    virtual ci::Rectf getBounds();
    virtual float getWidth();
    virtual float getHeight();

	virtual void mouseDown(const ci::Vec2i &pos);
	virtual void mouseDragged(const ci::Vec2i &pos);
	virtual void mouseUp(const ci::Vec2i &pos);
	virtual void mouseMoved(const ci::Vec2i &pos);
    
  protected:
    virtual void updateChildrenBounds();

	ci::Vec2f                   mOffset;
	ci::Rectf                   mBounds;

	std::vector<BasePretzel*>     mPretzelChildren;
    ci::Rectf                   mParentBounds;

	Pretzel::PretzelGlobal			*mGlobal;
};