#pragma once

#include "cinder/app/AppNative.h"

#include "pretzel/PretzelGlobal.h"
#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"

namespace Pretzel {
	class PretzelToggle : public BasePretzel {
	public:
		PretzelToggle(BasePretzel *parent, std::string label, bool *value);

		virtual void draw();
		void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

		virtual void mouseDown(const ci::Vec2i &pos);
        virtual void mouseMoved(const ci::Vec2i &pos);
        
        ci::signals::signal<void(void)> onChange;
        
	private:
		bool			*mValue;

		ci::Rectf		mCheckBoxRect;

		ci::Area		mSkinTexRect;
		ci::Rectf		mSkinDestRect;
        
        bool            bHover;
	};

}
