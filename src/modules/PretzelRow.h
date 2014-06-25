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
//		PretzelRow(BasePretzel *base, PretzelFillStyle width, int height);
//		PretzelRow(BasePretzel *base, int width, PretzelFillStyle height);
//		PretzelRow(BasePretzel *base, PretzelFillStyle width, PretzelFillStyle height);

		void draw();

		virtual void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

	protected:
		void updateChildrenBounds();

	private:
		void initPretzel(BasePretzel *base, int width, int height);

		bool        bFillWidth, bFillHeight;
	};
}