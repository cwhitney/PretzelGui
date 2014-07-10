//
//  ScrollPane.h
//  BasicSample
//
//  Created by Charlie Whitney on 6/24/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"

#include "PretzelRow.h"
#include "BasePretzel.h"

namespace Pretzel {

    class ScrollPane : public PretzelRow {
      public:
        ScrollPane(BasePretzel *base, int width, int height);
        virtual void draw();
        
        virtual void mouseDown(const ci::Vec2i &pos);
		virtual void mouseDragged(const ci::Vec2i &pos);
		virtual void mouseUp(const ci::Vec2i &pos);
		virtual void mouseMoved(const ci::Vec2i &pos);
        
      protected:
        void updateChildrenBounds();
        
        float       mScrolledPct;
        ci::Vec2f   mScrolledHandleAmt;
        ci::Vec2f   mScrolledFrameAmt;
        
        float       mChildrenHeight;
        bool        bCanScroll;
        
        ci::Rectf   mScrollHandle;
        ci::Vec2i   mStartDragOffset;
        
        bool        bDragging;
        bool        bHover;
    };
}