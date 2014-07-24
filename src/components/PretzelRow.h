//
//  PretzelRow.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/Rand.h"

#include "PretzelGlobal.h"
#include "BasePretzel.h"
namespace Pretzel{
	class PretzelRow : public BasePretzel {
	public:
		PretzelRow(BasePretzel *base, int width, int height);
		void draw();

	protected:
		void updateChildrenBounds();

	private:
		void initPretzel(BasePretzel *base, int width, int height);

		bool bFillWidth, bFillHeight;
	};
}