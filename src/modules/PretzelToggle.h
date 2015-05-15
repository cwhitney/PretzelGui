#pragma once

#include "cinder/app/App.h"

#include "pretzel/PretzelGlobal.h"
#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"

namespace Pretzel {
	class PretzelToggle : public BasePretzel {
	public:
		PretzelToggle(BasePretzel *parent, std::string label, bool *value);

		virtual void draw();
		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds);

		virtual void mouseDown(const ci::vec2 &pos);
        virtual void mouseMoved(const ci::vec2 &pos);
        
	private:
		bool			*mValue;
		std::string		mLabel;

		ci::Rectf		mCheckBoxRect;

		ci::Area		mSkinTexRect;
		ci::Rectf		mSkinDestRect;
        
        bool            bHover;
	};

}
