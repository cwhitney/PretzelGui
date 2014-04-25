#pragma once

#include "PretzelGlobal.h"
#include "BasePretzel.h"
#include "cinder/app/AppNative.h"
#include "PretzelGlobal.h"

namespace Pretzel {
	class PretzelToggle : public BasePretzel {
	public:
		PretzelToggle(BasePretzel *parent, std::string label, bool *value);

		virtual void draw();
		void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

		virtual void mouseDown(const ci::Vec2i &pos);

	private:
		bool			*mValue;
		std::string		mLabel;

		ci::Rectf		mCheckBoxRect;

		ci::Area		mSkinTexRect;
		ci::Rectf		mSkinDestRect;
	};

}
