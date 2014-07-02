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
        
      protected:
        void updateChildrenBounds();
        float mChildrenHeight;
    };
}