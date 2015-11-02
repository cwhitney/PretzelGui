#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"
namespace pretzel{
	class PretzelLabel : public BasePretzel {
	public:
		PretzelLabel(BasePretzel *parent, std::string labelText);

		virtual void draw();

		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds);

        ci::vec2    scrollPaneOffset;
        
	private:
		std::string		mMessage;
		ci::Path2d		mOutlinePath;
	};
}