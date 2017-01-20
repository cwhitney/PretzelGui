#include "PretzelEnum.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel{
	PretzelEnum::PretzelEnum(BasePretzel *parent, std::string labelText, std::vector<std::string> *strList, int *num) :
        BasePretzel(),
        mStrList(strList),
        mCurItem(num),
        mLabel(labelText)
    {
        if(mLabel != ""){
            mBounds.set(0, 0, 200, 46);
        }else{
            mBounds.set(0, 0, 200, 23);
        }
        
        type        = WidgetType::ENUM;
        mMinusBg    = mGlobal->P_TAB_COLOR;
        mPlusBg     = mGlobal->P_TAB_COLOR;
        
		parent->registerPretzel(this);
	}

	void PretzelEnum::updateBounds(const ci::vec2 &offset, const ci::RectT<float> &parentBounds) {
		BasePretzel::updateBounds(offset, parentBounds);

		int gap         = 2;
        int btnWidth    = 18;
        int bot         = mBounds.y2 - 26;
        
        mRectMinus = Rectf(mBounds.getWidth() - (btnWidth*2.0) - gap*2, bot, mBounds.getWidth() - btnWidth - gap*2, bot + btnWidth );
        mRectPlus = Rectf(mBounds.getWidth() - btnWidth-gap, bot, mBounds.getWidth()-gap, bot+btnWidth);
        mRectText = Rectf(10, bot, mRectMinus.x1 - gap, bot+btnWidth );
	}

	void PretzelEnum::mouseDown(const ci::vec2 &pos){
		if (mRectMinus.contains(pos - mOffset)){
            if(*mCurItem == 0){ *mCurItem = mStrList->size()-1; }
            else *mCurItem = *mCurItem-1;
            
            mMinusBg = mGlobal->P_ACTIVE_COLOR;
		}
		else if (mRectPlus.contains(pos - mOffset)){
            *mCurItem = *mCurItem+1;
            if(*mCurItem >= mStrList->size()){ *mCurItem = 0; }
            mPlusBg = mGlobal->P_ACTIVE_COLOR;
		}
	}

	void PretzelEnum::mouseMoved(const ci::vec2 &pos){
		if (mRectMinus.contains(pos - mOffset)){
			bHoverMinus = true;
			bHoverPlus = false;
            mGlobal->setCursor( CursorType::HAND );
            mMinusBg = mGlobal->P_HOVER_COLOR;
            mPlusBg = mGlobal->P_TAB_COLOR;
		}
		else if (mRectPlus.contains(pos - mOffset)){
			bHoverMinus = false;
			bHoverPlus = true;
            mGlobal->setCursor( CursorType::HAND );
            mMinusBg = mGlobal->P_TAB_COLOR;
            mPlusBg = mGlobal->P_HOVER_COLOR;
		}
		else{
            if( bHoverMinus || bHoverPlus ){
                mGlobal->setCursor( CursorType::ARROW );
            }
            mMinusBg = mGlobal->P_TAB_COLOR;
            mPlusBg = mGlobal->P_TAB_COLOR;
			bHoverMinus = false;
			bHoverPlus = false;
		}
	}
    
    void PretzelEnum::mouseUp(const ci::vec2 &pos){
        mMinusBg = mGlobal->P_TAB_COLOR;
        mPlusBg = mGlobal->P_TAB_COLOR;
    }

	void PretzelEnum::draw() {
        gl::ScopedMatrices scMat;
    
        gl::translate(mOffset + vec2(0, 3));

        // LABEL
        if( mLabel != ""){
            gl::ScopedColor scLb( pretzel()->P_TEXT_COLOR );
            mGlobal->renderText(mLabel, vec2(10, 1));
        }
        
        // TEXT
        gl::ScopedColor scC(mGlobal->P_HIGHLIGHT_COLOR);
        gl::drawStrokedRect(mRectText);
        pretzel()->renderText(mStrList->at(*mCurItem), vec2(mRectText.x1 + 4, mRectText.y1 + 3));
        
        // MINUS
        {
            gl::color( mMinusBg );
            PWindow()->drawSolidRect(mRectMinus);
            
            gl::color(mGlobal->P_HIGHLIGHT_COLOR);
            PWindow()->drawLine(mRectMinus.getUpperLeft() + vec2(0, 1), mRectMinus.getUpperRight() + vec2(0, 1));

            gl::color(mGlobal->P_OUTLINE_COLOR);
            PWindow()->drawStrokedRect(mRectMinus);
            mGlobal->renderTextCentered("-", vec2(mRectMinus.getCenter().x, mRectMinus.y1 + 2));
        }
        // PLUS
        {
            gl::color( mPlusBg );
            PWindow()->drawSolidRect(mRectPlus);

            gl::color(mGlobal->P_HIGHLIGHT_COLOR);
            PWindow()->drawLine(mRectPlus.getUpperLeft() + vec2(0, 1), mRectPlus.getUpperRight() + vec2(0, 1));

            gl::color(mGlobal->P_OUTLINE_COLOR);
            PWindow()->drawStrokedRect(mRectPlus);
            mGlobal->renderTextCentered("+", vec2(mRectPlus.getCenter().x, mRectPlus.y1 + 2));
        }
	}
}
