#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"

namespace pretzel
{
	class PretzelEnum : public BasePretzel
    {
	  public:
		PretzelEnum(BasePretzel *parent, std::string labelText, std::vector<std::string> *strList, int *num);
      
		void draw() override;
		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) override;

		void mouseDown(const ci::vec2 &pos) override;
		void mouseMoved(const ci::vec2 &pos) override;
        void mouseUp(const ci::vec2 &pos) override;
      private:
        std::string                 mLabel;
        std::vector<std::string>    *mStrList;
        int                         *mCurItem;
        
		ci::Rectf		mRectMinus, mRectPlus, mRectText;
		bool			bHoverMinus, bHoverPlus;
        
        ci::Color       mMinusBg, mPlusBg;
	};
}
