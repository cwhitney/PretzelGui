#pragma once

#include "PanelGlobal.h"
#include "BasePanel.h"
#include "cinder/app/AppNative.h"

class PanelSaveLoad: public BasePanel {
public:
	PanelSaveLoad(BasePanel *parent);
	PanelSaveLoad(BasePanel *parent, ci::fs::path savePath);
	
	virtual void draw();
	void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

	virtual void mouseDown(const ci::Vec2i &pos);
	virtual void mouseDragged(const ci::Vec2i &pos);
	virtual void mouseUp(const ci::Vec2i &pos);

private:
	ci::fs::path	mSavePath;
	ci::Rectf		mSaveRect, mLoadRect;
};

