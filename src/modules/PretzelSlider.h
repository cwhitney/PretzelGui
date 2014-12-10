#pragma once

#include "cinder/app/AppNative.h"

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"

namespace Pretzel {
    
    // -----------------------------------------------------------------------------------------------------
    template<typename T>
    class PSliderT {
      public:
        PSliderT(){};
        
        void setup(const std::string label, T *value, const T min, const T max, const ci::vec2 sliderLeft, const ci::vec2 sliderRight );
        
        virtual void draw();
		virtual void mouseDown(const ci::vec2 &pos);
		virtual void mouseDragged(const ci::vec2 &pos);
		virtual void mouseUp(const ci::vec2 &pos);
		virtual void mouseMoved(const ci::vec2 &pos);
        
        void updateBounds(const ci::vec2 sliderLeft, const ci::vec2 sliderRight);
        
        const std::string getLabel(){ return mLabelText; }
        const T getValue(){ return *mValue; }
        const float getNormalized(){ return (float)(mHandlePos.x - mSliderLeft.x) / (float)(mSliderRight.x - mSliderLeft.x); }
        
      private:
        void updateValue(const T val);
            
        T               *mValue;
        T               mMin, mMax;
        ci::vec2		mHandlePos;
		ci::Rectf		mHandleHitbox;
		ci::Area		mSkinTexRect;
		ci::Rectf		mSkinDestRect;
        
		ci::vec2		mSliderLeft, mSliderRight;
        float           mSliderPct;
        bool            bIsDragging;
        PretzelGlobal   *mGlobal;
        bool            mHandHover;
        std::string     mLabelText;
        
        float           mPosOffset;
    };
    
    // -----------------------------------------------------------------------------------------------------
    typedef PSliderT<float>  PSliderf;
    typedef PSliderT<int>    PSlideri;
    
    // -----------------------------------------------------------------------------------------------------
	class PretzelSlider : public BasePretzel {
	public:
		PretzelSlider(BasePretzel *parent, std::string labelText, float *value, float min, float max);
		PretzelSlider(BasePretzel *parent, std::string labelText, int *value, int min, int max);
        PretzelSlider(BasePretzel *parent, std::string labelText, ci::vec2 *value, ci::vec2 min, ci::vec2 max);
        PretzelSlider(BasePretzel *parent, std::string labelText, ci::vec3 *value, ci::vec3 min, ci::vec3 max);

		virtual void draw();

		virtual void mouseDown(const ci::vec2 &pos);
		virtual void mouseDragged(const ci::vec2 &pos);
		virtual void mouseUp(const ci::vec2 &pos);
		virtual void mouseMoved(const ci::vec2 &pos);

		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds);

	private:
        std::vector<PSliderf>   mSliderListf;
        std::vector<PSlideri>   mSliderListi;
        
        ci::vec2   mLineOffset;
	};
    // ------------------------------------------------------------------------------------------------------
}