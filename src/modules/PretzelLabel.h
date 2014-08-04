#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/AppNative.h"
namespace Pretzel{
	class PretzelLabel : public BasePretzel {
	public:
		PretzelLabel(BasePretzel *parent, std::string labelText);

		virtual void draw();

		void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

	private:
		std::string		mMessage;
		ci::Path2d		mOutlinePath;
	};
}