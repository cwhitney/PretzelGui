#include "PretzelSlider.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel{

    // =========================================================================================================================================    
    template<typename T>
    void PSliderT<T>::setup(const std::string label, T *value, const T min, const T max, ci::vec2 sliderLeft, ci::vec2 sliderRight ) {
        mLabelText = label;
        mValue = value;
        mMin = min;
        mMax = max;
        mSliderLeft = sliderLeft;
        mSliderRight = sliderRight;
        mPosOffset = 0;
//        type = WidgetType::SLIDER;
        
        // texture skin rect
		mSkinTexRect.set(0, 0, 13, 12);
		mSkinDestRect = mSkinTexRect;
		mSkinDestRect.offset(vec2(-7, -7));
        
        bIsDragging = false;
        mHandlePos = vec2(15, 22);
        mHandleHitbox.set(-5, -7, 5, 5);
        mSliderPct = 0.0f;
        
        mGlobal = PretzelGlobal::getInstance();
        
        updateBounds( mSliderLeft, mSliderRight );
    }
    
    template<typename T>
    void PSliderT<T>::updateBounds(const ci::vec2 sliderLeft, const ci::vec2 sliderRight){
        mSliderLeft = sliderLeft;
        mSliderRight = sliderRight;
        
        mPosOffset = sliderLeft.y - 22;
        
        updateValue( *mValue );
    }
    
    template<typename T>
    void PSliderT<T>::updateValue(const T val){
        T tVal = val;
		if (mMin < mMax){
			tVal = math<T>::clamp(val, mMin, mMax);
		}else{
			tVal = math<T>::clamp(val, mMax, mMin);
		}
        
        *mValue = tVal;
        mSliderPct = (float)(tVal - mMin) / (float)(mMax - mMin);
        
		mHandlePos.x = lerp(mSliderLeft.x, mSliderRight.x, mSliderPct);
	}
    
    template<typename T>
    void PSliderT<T>::mouseDown(const vec2 &pos){
        vec2 localPos = pos - mHandlePos - ci::vec2(0, mPosOffset);
        
        if( mHandleHitbox.contains(localPos) ){
            bIsDragging = true;
            mHandlePos.x = pos.x;
        }
	}
    
    template<typename T>
    void PSliderT<T>::mouseMoved(const ci::vec2 &pos){
        vec2 localPos = pos - mHandlePos - ci::vec2(0, mPosOffset);
        
        if( mHandleHitbox.contains(localPos) ){
            mHandHover = true;
            mGlobal->setCursor(CursorType::HAND);
        }else{
            if( mHandHover ){
                mGlobal->setCursor(CursorType::ARROW);
            }
            mHandHover = false;
        }
	}
    
    template<typename T>
	void PSliderT<T>::mouseDragged(const vec2 &pos){
		if (bIsDragging){
			mHandlePos.x = ci::math<float>::clamp(pos.x, mSliderLeft.x, mSliderRight.x);
			mSliderPct = lmap<float>(mHandlePos.x, mSliderLeft.x, mSliderRight.x, 0.0, 1.0);
            
            *mValue = (mMax - mMin) * mSliderPct + mMin;
		}
	}
    
    template<typename T>
	void PSliderT<T>::mouseUp(const vec2 &pos){
        if( bIsDragging ){
            bIsDragging = false;
            mGlobal->setCursor(CursorType::ARROW);
        }
		
	}
    
    template<typename T>
    void PSliderT<T>::draw(){
        
        gl::pushMatrices();{
            gl::color(mGlobal->P_SLIDER_COLOR);
            PWindow()->drawLine(mSliderLeft, mSliderRight);
            
            gl::translate(0, mPosOffset);
            
            
            gl::color(ColorA(1, 1, 1, 1));
            gl::pushMatrices(); {
                gl::translate(mHandlePos);
                gl::draw(mGlobal->mSkinTex, mSkinTexRect, mSkinDestRect);
            }gl::popMatrices();
        }gl::popMatrices();
    }

    // =========================================================================================================================================
	PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, int *value, int minVal, int maxVal) : BasePretzel(){
        mBounds.set(0, 0, 200, 30);
        
        vec2 slideL = mBounds.getUpperLeft() + vec2(10, 22);
		vec2 slideR = mBounds.getUpperRight() + vec2(-10, 22);
        
        PSlideri newSlider;
        newSlider.setup(labelText, value, minVal, maxVal, slideL, slideR);
		mSliderListi.push_back( newSlider );
        
		mGlobal->addSaveParam(labelText, value);
        
		parent->registerPretzel(this);
	}

	PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, float *value, float minVal, float maxVal) : BasePretzel(){
		mBounds.set(0, 0, 200, 30);

        vec2 slideL = mBounds.getUpperLeft() + vec2(10, 22);
		vec2 slideR = mBounds.getUpperRight() + vec2(-10, 22);
        
        PSliderf newSlider;
        newSlider.setup(labelText, value, minVal, maxVal, slideL, slideR);
		mSliderListf.push_back( newSlider );
        
		mGlobal->addSaveParam(labelText, value);

		parent->registerPretzel(this);
	}
    
    PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, vec2 *value, vec2 minVal, vec2 maxVal) : BasePretzel(){
		mLineOffset = vec2(0, 14);
        mBounds.set(0, 0, 200, 30);
        mBounds.include( mBounds.getLowerRight() + mLineOffset + vec2(0,5) );
        
        vec2 slideL = mBounds.getUpperLeft() + vec2(30, 22);
		vec2 slideR = mBounds.getUpperRight() + vec2(-10, 22);
        
        PSliderf newSliderX;
        newSliderX.setup(labelText, &(value->x), minVal.x, maxVal.x, slideL, slideR);
        mSliderListf.push_back( newSliderX );
        
        PSliderf newSliderY;
        newSliderY.setup(labelText, &(value->y), minVal.y, maxVal.y, slideL + mLineOffset, slideR + mLineOffset);
        mSliderListf.push_back( newSliderY );

		mGlobal->addSaveParam(labelText, value);
        
		parent->registerPretzel(this);
	}
    
    PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, vec3 *value, vec3 minVal, vec3 maxVal) : BasePretzel(){
		mLineOffset = vec2(0, 14);
        mBounds.set(0, 0, 200, 30);
        mBounds.include( mBounds.getLowerRight() + mLineOffset * 2.f + vec2(0,5) );
        
        vec2 slideL = mBounds.getUpperLeft() + vec2(30, 22);
		vec2 slideR = mBounds.getUpperRight() + vec2(-10, 22);
        
        PSliderf newSliderX;
        newSliderX.setup(labelText, &(value->x), minVal.x, maxVal.x, slideL, slideR);
        mSliderListf.push_back( newSliderX );
        
        PSliderf newSliderY;
        newSliderY.setup(labelText, &(value->y), minVal.y, maxVal.y, slideL + mLineOffset, slideR + mLineOffset);
        mSliderListf.push_back( newSliderY );
        
        PSliderf newSliderZ;
        newSliderY.setup(labelText, &(value->z), minVal.z, maxVal.z, slideL + mLineOffset * 2.f, slideR + mLineOffset * 1.f);
        mSliderListf.push_back( newSliderY );
        
		mGlobal->addSaveParam(labelText, value);
        
		parent->registerPretzel(this);
	}

	void PretzelSlider::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds){
		BasePretzel::updateBounds(offset, parentBounds);

        vec2 slideL = mBounds.getUpperLeft() + vec2(10, 22);
		vec2 slideR = mBounds.getUpperRight() + vec2(-10, 22);
        
        if(mSliderListi.size() > 1 || mSliderListf.size() > 1){
            slideL = mBounds.getUpperLeft() + vec2(30, 22);
            slideR = mBounds.getUpperRight() + vec2(-10, 22);
        }
        
        for( int i=0; i<mSliderListi.size(); i++){
            mSliderListi[i].updateBounds(slideL + mLineOffset* float(i), slideR + mLineOffset* float(i));
        }

        for( int i=0; i<mSliderListf.size(); i++){
            mSliderListf[i].updateBounds(slideL + mLineOffset*float(i), slideR + mLineOffset*float(i));
        }
	}

	void PretzelSlider::mouseDown(const vec2 &pos){
		if (mBounds.contains(pos - mOffset)){
            for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
                it->mouseDown( pos - mOffset );
            }
            for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
                it->mouseDown( pos - mOffset );
            }
        }
	}

	void PretzelSlider::mouseMoved(const ci::vec2 &pos){
        if (mBounds.contains(pos - mOffset)){
            for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
                it->mouseMoved( pos - mOffset );
            }
            for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
                it->mouseMoved( pos - mOffset );
            }
        }
	}

	void PretzelSlider::mouseDragged(const vec2 &pos){
        for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
            it->mouseDragged( pos - mOffset );
        }
        for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
            it->mouseDragged( pos - mOffset );
        }
	}
	void PretzelSlider::mouseUp(const vec2 &pos){
        for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
            it->mouseUp( pos - mOffset );
        }
        for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
            it->mouseUp( pos - mOffset );
        }
	}

	void PretzelSlider::draw() {
		gl::pushMatrices(); {
			gl::translate(mOffset);

            if( mSliderListf.size() > 1 ){
                mGlobal->renderText(mSliderListf.front().getLabel(), mBounds.getUpperLeft() + vec2(12, 1));
                
                std::string sValues = "";
                int i=0;
                for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); it++){
                    if(i==0) mGlobal->renderText("x", vec2(12, 0 + 13) );
                    if(i==1) mGlobal->renderText("y", vec2(12, 15*i + 13) );
                    if(i==2) mGlobal->renderText("z", vec2(12, 15*i + 13) );
                    it->draw();
                    
                    sValues += mGlobal->to_string_with_precision( it->getValue() ) + ", ";
                    ++i;
                }
                sValues = sValues.substr(0, sValues.length()-2);
                mGlobal->renderTextRight( sValues, mBounds.getUpperRight() + vec2(-12, 1));
            }else{
                for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
                    mGlobal->renderText(it->getLabel(), mBounds.getUpperLeft() + vec2(12, 1));
                    mGlobal->renderTextRight( mGlobal->to_string_with_precision( it->getValue() ), mBounds.getUpperRight() + vec2(-12, 1));
                    it->draw();
                }
            }
            
            if( mSliderListi.size() > 1 ){
                
            }else{
                for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
                    mGlobal->renderText(it->getLabel(), mBounds.getUpperLeft() + vec2(12, 1));
                    mGlobal->renderTextRight( to_string(it->getValue()), mBounds.getUpperRight() + vec2(-12, 1));
                    it->draw();
                }
            }
            
		}gl::popMatrices();
	}
    // =========================================================================================================================================
}
