#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"

namespace pretzel
{
	class PretzelButton : public BasePretzel
    {
	  public:
		PretzelButton(BasePretzel *parent, std::string labeText);
        
		void draw() override;
		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) override;
        
        void mouseDown(const ci::vec2 &pos) override;
        void mouseUp(const ci::vec2 &pos) override;
		void mouseMoved(const ci::vec2 &pos) override;
        
        ci::signals::Signal<void(void)>	signalOnPress;
        ci::signals::ScopedConnection   mConnection;
        
      private:
		std::string		mLabelText;
		ci::Rectf		mButtonBounds;

		bool			bHover;
        ci::Color       mBgColor;
	};
}
