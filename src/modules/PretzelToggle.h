#pragma once

#include "cinder/app/App.h"

#include "pretzel/PretzelGlobal.h"
#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"

namespace pretzel {
	class PretzelToggle : public BasePretzel
    {
	  public:
        PretzelToggle(BasePretzel *parent, std::string label, bool *value);
        
        void draw() override;
        void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) override;
        
        void mouseDown(const ci::vec2 &pos) override;
        void mouseMoved(const ci::vec2 &pos) override;

      private:
		bool			*mValue;
		std::string		mLabel;

		ci::Rectf		mCheckBoxRect;

		ci::Area		mSkinTexRect;
		ci::Rectf		mSkinDestRect;
        
        bool            bHover;
	};

}
