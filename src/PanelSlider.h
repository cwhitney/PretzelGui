#pragma once

#include "cinder/app/AppNative.h"

#include "PanelGlobal.h"
#include "BasePanel.h"

class PanelSlider : public BasePanel {
public:
	PanelSlider(BasePanel *parent, std::string labelText, float *value, float min, float max);

	virtual void draw();

	virtual void mouseDown(const ci::Vec2i &pos);
	virtual void mouseDragged(const ci::Vec2i &pos);
	virtual void mouseUp(const ci::Vec2i &pos);

	void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

private:
	void updateValue( float newVal );

	std::string		mLabelText;
	float			*mValue;
	float			mMin, mMax;

	ci::Vec2f		mHandlePos;
	ci::Rectf		mHandleHitbox;

	ci::Vec2f		mSliderLeft, mSliderRight;

	bool			bIsDragging;
	float			mSliderPct;
};

