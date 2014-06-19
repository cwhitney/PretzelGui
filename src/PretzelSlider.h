#pragma once

#include "cinder/app/AppNative.h"

#include "PretzelGlobal.h"
#include "BasePretzel.h"

namespace Pretzel {
    
    class PSlide {
      public:
        PSlide();
        void setup(float *value, float min, float max, const ci::Vec2f sliderLeft, const ci::Vec2f sliderRight );
        
        virtual void draw();
        
		virtual void mouseDown(const ci::Vec2i &pos);
		virtual void mouseDragged(const ci::Vec2i &pos);
		virtual void mouseUp(const ci::Vec2i &pos);
		virtual void mouseMoved(const ci::Vec2i &pos);
      private:
        float			*mValue;
        float           mMin, mMax;
        ci::Vec2f		mHandlePos;
		ci::Rectf		mHandleHitbox;
		ci::Area		mSkinTexRect;
		ci::Rectf		mSkinDestRect;
        
		ci::Vec2f		mSliderLeft, mSliderRight;

    };
    
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
		void updateValue(float newVal);

        std::vector<PSlide> mSliderList;
        
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
        bool            mHandHover;
	};

}