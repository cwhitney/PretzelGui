#pragma once

#include "PanelGlobal.h"
#include "BasePanel.h"
#include "cinder/app/AppNative.h"

#include <boost/signals2.hpp>

class PanelButton : public BasePanel{
public:
	PanelButton(BasePanel *parent, std::string labeText);

	virtual void draw();
	void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

	virtual void mouseDown(const ci::Vec2i &pos);

	boost::signals2::signal<void(void)>	signalOnPress;
private:
	std::string		mLabelText;
	ci::Rectf		mButtonBounds;
};

