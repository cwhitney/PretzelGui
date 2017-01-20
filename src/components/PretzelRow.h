//
//  PretzelRow.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/Rand.h"

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"

namespace pretzel{
    
	class PretzelRow : public BasePretzel
    {
	  public:
		PretzelRow(BasePretzel *base, int width, int height);
        void draw() override;

	  protected:
		void updateChildrenBounds() override;
		void initPretzel(BasePretzel *base, int width, int height);
		bool bFillWidth, bFillHeight;
	};
}
