//
//  BasePretzel.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/App.h"
#include "pretzel/PretzelGlobal.h"

namespace Pretzel{
	class BasePretzel {
        
	public:
		BasePretzel();
        virtual ~BasePretzel();

		virtual void draw(){};
		virtual void registerPretzel(BasePretzel *child);

		virtual void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds);

		virtual ci::Rectf getBounds();
		virtual float getWidth();
		virtual float getHeight();

		virtual void mouseDown(const ci::vec2 &pos);
		virtual void mouseDragged(const ci::vec2 &pos);
		virtual void mouseUp(const ci::vec2 &pos);
		virtual void mouseMoved(const ci::vec2 &pos);
		virtual void keyDown(const char &key, const int &keyCode);
        
        virtual void updateChildrenBounds();
        
        BasePretzel* getParent();
        void setParent( BasePretzel *parent );
        
        WidgetType  type;

	protected:
        BasePretzel                 *mParent;
        
        // The offset from the app-wide 0,0 to the topLeft of the main gui window
        ci::vec2                   mGlobalOffset;
        
        // The offset from the 0,0 top-left of the main gui window to this particular module
		ci::vec2                   mOffset;
        
        // The containing bounds of this item where the upper-left of mBounds = mGlobalOffset + mOffset
		ci::Rectf             mBounds;

		std::vector<BasePretzel*>   mPretzelChildren;
		ci::Rectf            mParentBounds;
        
        

		Pretzel::PretzelGlobal		*mGlobal;
	};
}