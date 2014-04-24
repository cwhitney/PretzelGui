#pragma once

#include "cinder/app/AppNative.h"

#include "PretzelGlobal.h"
#include "BasePretzel.h"

class PretzelSlider : public BasePretzel {
public:
	PretzelSlider(BasePretzel *parent, std::string labelText, float *value, float min, float max);
	PretzelSlider(BasePretzel *parent, std::string labelText, int *value, int min, int max);

	virtual void draw();

	virtual void mouseDown(const ci::Vec2i &pos);
	virtual void mouseDragged(const ci::Vec2i &pos);
	virtual void mouseUp(const ci::Vec2i &pos);
	virtual void mouseMoved(const ci::Vec2i &pos);

	void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

private:
	void updateValue( float newVal );

	std::string		mLabelText;
	float			*mValue;
	float			mMin, mMax;

	int				*mValueInt;

	ci::Vec2f		mHandlePos;
	ci::Rectf		mHandleHitbox;
	ci::Area		mSkinTexRect;
	ci::Rectf		mSkinDestRect;

	ci::Vec2f		mSliderLeft, mSliderRight;

	bool			bIsDragging;
	float			mSliderPct;
	bool			bUseInteger;
};

