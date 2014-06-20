#pragma once

#include "cinder/app/AppNative.h"

#include "PretzelGlobal.h"
#include "BasePretzel.h"

namespace Pretzel {
    
    // -----------------------------------------------------------------------------------------------------
    template<typename T>
    class PSliderT {
      public:
        PSliderT(){};
        
        void setup(const std::string label, T *value, const T min, const T max, const ci::Vec2<T> sliderLeft, const ci::Vec2<T> sliderRight );
        
        virtual void draw();
		virtual void mouseDown(const ci::Vec2i &pos);
		virtual void mouseDragged(const ci::Vec2i &pos);
		virtual void mouseUp(const ci::Vec2i &pos);
		virtual void mouseMoved(const ci::Vec2i &pos);
        
        void updateBounds(const ci::Vec2<T> sliderLeft, const ci::Vec2<T> sliderRight);
        
        const std::string getLabel(){ return mLabelText; }
        const T getValue(){ return *mValue; }
        
      private:
        void updateValue(const T val);
            
        T               *mValue;
        T               mMin, mMax;
        ci::Vec2<T>		mHandlePos;
		ci::Rectf		mHandleHitbox;
		ci::Area		mSkinTexRect;
		ci::Rectf		mSkinDestRect;
        
		ci::Vec2<T>		mSliderLeft, mSliderRight;
        float           mSliderPct;
        bool            bIsDragging;
        PretzelGlobal   *mGlobal;
        bool            mHandHover;
        std::string     mLabelText;
    };
    
    // -----------------------------------------------------------------------------------------------------
    typedef PSliderT<float>  PSliderf;
    typedef PSliderT<int>    PSlideri;
    
    // -----------------------------------------------------------------------------------------------------
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
        std::vector<PSliderf> mSliderListf;
        std::vector<PSlideri> mSliderListi;
	};
    // ------------------------------------------------------------------------------------------------------
}