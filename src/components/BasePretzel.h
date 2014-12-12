//
//  BasePretzel.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include <boost/algorithm/string.hpp>
#include "pretzel/PretzelGlobal.h"

namespace Pretzel{
	class BasePretzel {
        
	public:
		BasePretzel();
        virtual ~BasePretzel();

		virtual void draw(){};
		virtual void registerPretzel(BasePretzel *child);

		virtual void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

		virtual ci::Rectf getBounds();
		virtual float getWidth();
		virtual float getHeight();
        std::string getName();

		virtual void mouseDown(const ci::Vec2i &pos);
		virtual void mouseDragged(const ci::Vec2i &pos);
		virtual void mouseUp(const ci::Vec2i &pos);
		virtual void mouseMoved(const ci::Vec2i &pos);
		virtual void keyDown(const char &key, const int &keyCode);
        
        virtual void updateChildrenBounds();
        
        BasePretzel* getParent();
        void setParent( BasePretzel *parent );
        
        WidgetType  type;
        

	protected:
        BasePretzel                 *mParent;
        std::string                 mLabel;
        
        // The offset from the app-wide 0,0 to the topLeft of the main gui window
        ci::Vec2f                   mGlobalOffset;
        
        // The offset from the 0,0 top-left of the main gui window to this particular module
		ci::Vec2f                   mOffset;
        
        // The containing bounds of this item where the upper-left of mBounds = mGlobalOffset + mOffset
		ci::Rectf                   mBounds;

		std::vector<BasePretzel*>   mPretzelChildren;
		ci::Rectf                   mParentBounds;
        
        

		Pretzel::PretzelGlobal		*mGlobal;
	};
}