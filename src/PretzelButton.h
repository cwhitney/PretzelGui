#pragma once

#include "PretzelGlobal.h"
#include "BasePretzel.h"
#include "cinder/app/AppNative.h"
#include <boost/signals2.hpp>

namespace Pretzel{
	class PretzelButton : public BasePretzel{
	public:
		PretzelButton(BasePretzel *parent, std::string labeText);

		virtual void draw();
		void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

		virtual void mouseDown(const ci::Vec2i &pos);
		virtual void mouseMoved(const ci::Vec2i &pos);

		boost::signals2::signal<void(void)>	signalOnPress;
        
        boost::signals2::scoped_connection  mConnection;
	private:
		std::string		mLabelText;
		ci::Rectf		mButtonBounds;

		bool			bHover;
	};
}