#pragma once

#include "cinder/app/AppNative.h"
#include "BasePanel.h"

class BaseComponent
{
public:
	virtual void draw(){};

	virtual void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

	virtual ci::Rectf getBounds();
	virtual float getWidth();
	virtual float getHeight();

protected:
	virtual void updateChildrenBounds();

	std::vector<BasePanel*>     mPanelChildren;
	ci::Vec2f                   mOffset;
	ci::Rectf                   mParentBounds;
	ci::Rectf                   mBounds;
};

