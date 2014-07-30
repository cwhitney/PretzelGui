#include "PretzelSlider.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel{

    // =========================================================================================================================================    
    template<typename T>
    void PSliderT<T>::setup(const std::string label, T *value, const T min, const T max, ci::Vec2<T> sliderLeft, ci::Vec2<T> sliderRight ){
        mLabelText = label;
        mValue = value;
        mMin = min;
        mMax = max;
        mSliderLeft = sliderLeft;
        mSliderRight = sliderRight;
        mPosOffset = 0;
        
        // texture skin rect
		mSkinTexRect.set(0, 0, 13, 12);
		mSkinDestRect = mSkinTexRect;
		mSkinDestRect.offset(Vec2i(-7, -7));
        
        bIsDragging = false;
        mHandlePos.set(15, 22);
        mHandleHitbox.set(-5, -7, 5, 5);
        mSliderPct = 0.0f;
        
        mGlobal = PretzelGlobal::getInstance();
        
        updateBounds( mSliderLeft, mSliderRight );
    }
    
    template<typename T>
    void PSliderT<T>::updateBounds(const ci::Vec2<T> sliderLeft, const ci::Vec2<T> sliderRight){
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
    void PSliderT<T>::mouseDown(const Vec2i &pos){
        Vec2f localPos = pos - mHandlePos - Vec2f(0, mPosOffset);
        
        if( mHandleHitbox.contains(localPos) ){
            bIsDragging = true;
            mHandlePos.x = pos.x;
        }
	}
    
    template<typename T>
    void PSliderT<T>::mouseMoved(const ci::Vec2i &pos){
        Vec2f localPos = pos - mHandlePos - Vec2f(0, mPosOffset);
        
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
	void PSliderT<T>::mouseDragged(const Vec2i &pos){
		if (bIsDragging){
			mHandlePos.x = ci::math<float>::clamp(pos.x, mSliderLeft.x, mSliderRight.x);
			mSliderPct = lmap<float>(mHandlePos.x, mSliderLeft.x, mSliderRight.x, 0.0, 1.0);
            
            *mValue = (mMax - mMin) * mSliderPct + mMin;
		}
	}
    
    template<typename T>
	void PSliderT<T>::mouseUp(const Vec2i &pos){
        if( bIsDragging ){
            bIsDragging = false;
            mGlobal->setCursor(CursorType::ARROW);
        }
		
	}
    
    template<typename T>
    void PSliderT<T>::draw(){
        
        gl::pushMatrices();{
            gl::color(mGlobal->P_SLIDER_COLOR);
            gl::drawLine(mSliderLeft, mSliderRight);
            
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
        
        Vec2f slideL = mBounds.getUpperLeft() + Vec2f(10, 22);
		Vec2f slideR = mBounds.getUpperRight() + Vec2f(-10, 22);
        
        PSlideri newSlider;
        newSlider.setup(labelText, value, minVal, maxVal, slideL, slideR);
		mSliderListi.push_back( newSlider );
        
		mGlobal->addSaveParam(labelText, value);
        
		parent->registerPretzel(this);
	}

	PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, float *value, float minVal, float maxVal) : BasePretzel(){
		mBounds.set(0, 0, 200, 30);

        Vec2f slideL = mBounds.getUpperLeft() + Vec2f(10, 22);
		Vec2f slideR = mBounds.getUpperRight() + Vec2f(-10, 22);
        
        PSliderf newSlider;
        newSlider.setup(labelText, value, minVal, maxVal, slideL, slideR);
		mSliderListf.push_back( newSlider );
        
		mGlobal->addSaveParam(labelText, value);

		parent->registerPretzel(this);
	}
    
    PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, Vec2f *value, Vec2f minVal, Vec2f maxVal) : BasePretzel(){
		mLineOffset.set(0, 14);
        mBounds.set(0, 0, 200, 30);
        mBounds.include( mBounds.getLowerRight() + mLineOffset + Vec2f(0,5) );
        
        Vec2f slideL = mBounds.getUpperLeft() + Vec2f(30, 22);
		Vec2f slideR = mBounds.getUpperRight() + Vec2f(-10, 22);
        
        PSliderf newSliderX;
        newSliderX.setup(labelText, &(value->x), minVal.x, maxVal.x, slideL + mLineOffset * 0, slideR + mLineOffset * 0);
        mSliderListf.push_back( newSliderX );
        
        PSliderf newSliderY;
        newSliderY.setup(labelText, &(value->y), minVal.y, maxVal.y, slideL + mLineOffset * 1, slideR + mLineOffset * 1);
        mSliderListf.push_back( newSliderY );

		mGlobal->addSaveParam(labelText, value);
        
		parent->registerPretzel(this);
	}
    
    PretzelSlider::PretzelSlider(BasePretzel *parent, std::string labelText, Vec3f *value, Vec3f minVal, Vec3f maxVal) : BasePretzel(){
		mLineOffset.set(0, 14);
        mBounds.set(0, 0, 200, 30);
        mBounds.include( mBounds.getLowerRight() + mLineOffset*2 + Vec2f(0,5) );
        
        Vec2f slideL = mBounds.getUpperLeft() + Vec2f(30, 22);
		Vec2f slideR = mBounds.getUpperRight() + Vec2f(-10, 22);
        
        PSliderf newSliderX;
        newSliderX.setup(labelText, &(value->x), minVal.x, maxVal.x, slideL + mLineOffset * 0, slideR + mLineOffset * 0);
        mSliderListf.push_back( newSliderX );
        
        PSliderf newSliderY;
        newSliderY.setup(labelText, &(value->y), minVal.y, maxVal.y, slideL + mLineOffset * 1, slideR + mLineOffset * 1);
        mSliderListf.push_back( newSliderY );
        
        PSliderf newSliderZ;
        newSliderY.setup(labelText, &(value->z), minVal.z, maxVal.z, slideL + mLineOffset * 2, slideR + mLineOffset * 1);
        mSliderListf.push_back( newSliderY );
        
		mGlobal->addSaveParam(labelText, value);
        
		parent->registerPretzel(this);
	}

	void PretzelSlider::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
		BasePretzel::updateBounds(offset, parentBounds);

        Vec2f slideL = mBounds.getUpperLeft() + Vec2f(10, 22);
		Vec2f slideR = mBounds.getUpperRight() + Vec2f(-10, 22);
        
        if(mSliderListi.size() > 1 || mSliderListf.size() > 1){
            slideL = mBounds.getUpperLeft() + Vec2f(30, 22);
            slideR = mBounds.getUpperRight() + Vec2f(-10, 22);
        }
        
        for( int i=0; i<mSliderListi.size(); i++){
            mSliderListi[i].updateBounds(slideL + mLineOffset*i, slideR + mLineOffset*i);
        }

        for( int i=0; i<mSliderListf.size(); i++){
            mSliderListf[i].updateBounds(slideL + mLineOffset*i, slideR + mLineOffset*i);
        }
	}

	void PretzelSlider::mouseDown(const Vec2i &pos){
		if (mBounds.contains(pos - mOffset)){
            for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
                it->mouseDown( pos - mOffset );
            }
            for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
                it->mouseDown( pos - mOffset );
            }
        }
	}

	void PretzelSlider::mouseMoved(const ci::Vec2i &pos){
        if (mBounds.contains(pos - mOffset)){
            for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
                it->mouseMoved( pos - mOffset );
            }
            for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
                it->mouseMoved( pos - mOffset );
            }
        }
	}

	void PretzelSlider::mouseDragged(const Vec2i &pos){
        for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
            it->mouseDragged( pos - mOffset );
        }
        for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
            it->mouseDragged( pos - mOffset );
        }
	}
	void PretzelSlider::mouseUp(const Vec2i &pos){
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
                mGlobal->renderText(mSliderListf.front().getLabel(), mBounds.getUpperLeft() + Vec2i(12, 1));
                
                std::string sValues = "";
                int i=0;
                for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); it++){
                    if(i==0) mGlobal->renderText("x", Vec2f(12, 0 + 13) );
                    if(i==1) mGlobal->renderText("y", Vec2f(12, 15*i + 13) );
                    if(i==2) mGlobal->renderText("z", Vec2f(12, 15*i + 13) );
                    it->draw();
                    
                    sValues += mGlobal->to_string_with_precision( it->getValue() ) + ", ";
                    ++i;
                }
                sValues = sValues.substr(0, sValues.length()-2);
                mGlobal->renderTextRight( sValues, mBounds.getUpperRight() + Vec2i(-12, 1));
            }else{
                for( auto it=mSliderListf.begin(); it!=mSliderListf.end(); ++it){
                    mGlobal->renderText(it->getLabel(), mBounds.getUpperLeft() + Vec2i(12, 1));
                    mGlobal->renderTextRight( mGlobal->to_string_with_precision( it->getValue() ), mBounds.getUpperRight() + Vec2i(-12, 1));
                    it->draw();
                }
            }
            
            if( mSliderListi.size() > 1 ){
                
            }else{
                for( auto it=mSliderListi.begin(); it!=mSliderListi.end(); ++it){
                    mGlobal->renderText(it->getLabel(), mBounds.getUpperLeft() + Vec2i(12, 1));
                    mGlobal->renderTextRight( to_string(it->getValue()), mBounds.getUpperRight() + Vec2i(-12, 1));
                    it->draw();
                }
            }
            
		}gl::popMatrices();
	}
    // =========================================================================================================================================
}