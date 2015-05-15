#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"
#include <boost/signals2.hpp>

namespace Pretzel{
	class PretzelButton : public BasePretzel{
	public:
		PretzelButton(BasePretzel *parent, std::string labeText);

		virtual void draw();
		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds);

		virtual void mouseDown(const ci::vec2 &pos);
        virtual void mouseUp(const ci::vec2 &pos);
		virtual void mouseMoved(const ci::vec2 &pos);

		boost::signals2::signal<void(void)>	signalOnPress;
        
        boost::signals2::scoped_connection  mConnection;
	private:
		std::string		mLabelText;
		ci::Rectf		mButtonBounds;

		bool			bHover;
        ci::Color       mBgColor;
	};
}