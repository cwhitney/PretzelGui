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
#include "components/WindowSystem.h"

namespace pretzel {
	
    class PretzelGlobal;
    
    /**
     * This is the base class for all gui visual elements including Modules and Rows.
     */
    class BasePretzel {
        
	public:
		BasePretzel();
        ~BasePretzel();

        virtual void update();
        virtual void draw() {};
		virtual void registerPretzel(BasePretzel *child);
		virtual void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds);

        virtual ci::Rectf getBounds();
        virtual ci::Rectf getGlobalBounds();
		float getWidth();
		float getHeight();
        
        BasePretzel* getParent();
        void setParent( BasePretzel *parent );
        
        WidgetType  type;
        
        virtual void mouseDown(const ci::vec2 &pos);
        virtual void mouseDragged(const ci::vec2 &pos);
        virtual void mouseUp(const ci::vec2 &pos);
        virtual void mouseMoved(const ci::vec2 &pos);
        virtual void mouseWheel(const float increment);
        virtual void keyDown(const char &key, const int &keyCode);

        virtual void updateChildrenBounds();

        // Offset of a module local to it's gui window.
        const ci::vec2 getOffset(){ return mOffset; }
        
    protected:
        BasePretzel                 *mParent;
        
        // The offset from the app-wide 0,0 to the topLeft of the gui window
        ci::vec2                    mGlobalOffset;
        
        // The offset from the 0,0 top-left of the main gui window to this particular module
		ci::vec2                    mOffset;
        
        // The containing bounds of this item where the upper-left of mBounds = mGlobalOffset + mOffset
		ci::Rectf                   mBounds;

		std::vector<BasePretzel*>   mPretzelChildren;
		ci::Rectf                   mParentBounds;
        
        PretzelGlobal               *mGlobal;
	};
}
