#pragma once

#include "PretzelGlobal.h"
#include "BasePretzel.h"
#include "cinder/app/AppNative.h"

namespace Pretzel{
	class PretzelSaveLoad : public BasePretzel {
	public:
		PretzelSaveLoad(BasePretzel *parent);
		PretzelSaveLoad(BasePretzel *parent, ci::fs::path savePath);

		virtual void draw();
		void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

		virtual void mouseDown(const ci::Vec2i &pos);
		virtual void mouseMoved(const ci::Vec2i &pos);
        virtual void mouseUp(const ci::Vec2i &pos);
        
	private:
		ci::fs::path	mSavePath;
		ci::Rectf		mSaveRect, mLoadRect;
		bool			bHoverSave, bHoverLoad;
        
        ci::Color       mSaveBg, mLoadBg;
	};
}