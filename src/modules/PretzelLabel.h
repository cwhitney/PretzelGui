#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"

namespace pretzel
{
	class PretzelLabel : public BasePretzel
    {
        friend class ScrollPane;
        
	  public:
		PretzelLabel(BasePretzel *parent, std::string labelText);
        void draw() override;
        void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) override;
        
		std::string getText() { return mMessage; }

      private:
		std::string		mMessage;
		ci::Path2d		mOutlinePath;
        ci::vec2        scrollPaneOffset;
	};
}