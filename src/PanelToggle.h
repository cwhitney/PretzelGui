#pragma once

#include "PanelGlobal.h"
#include "BasePanel.h"
#include "cinder/app/AppNative.h"
#include "PanelGlobal.h"


class PanelToggle : public BasePanel {
public:
	PanelToggle(BasePanel *parent, std::string label, bool *value);
	
	virtual void draw();
	void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

	virtual void mouseDown(const ci::Vec2i &pos);

private:
	bool			*mValue;
	std::string		mLabel;
};

