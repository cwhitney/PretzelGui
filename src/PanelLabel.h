#pragma once

#include "PanelGlobal.h"
#include "BasePanel.h"
#include "cinder/app/AppNative.h"

class PanelLabel : public BasePanel {
public:
	PanelLabel(BasePanel *parent, std::string labelText);

	virtual void registerPanel(BasePanel *panel);
	virtual void draw();

	void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

private:
	std::string		mMessage;
	ci::Path2d		mOutlinePath;
};