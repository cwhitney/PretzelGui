#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"

namespace Pretzel{
	class PretzelSaveLoad : public BasePretzel {
	public:
		PretzelSaveLoad(BasePretzel *parent);
		PretzelSaveLoad(BasePretzel *parent, ci::fs::path savePath);

		virtual void draw();
		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds);

		virtual void mouseDown(const ci::vec2 &pos);
		virtual void mouseMoved(const ci::vec2 &pos);
        virtual void mouseUp(const ci::vec2 &pos);
        
	private:
		ci::fs::path	mSavePath;
		ci::Rectf		mSaveRect, mLoadRect;
		bool			bHoverSave, bHoverLoad;
        
        ci::Color       mSaveBg, mLoadBg;
	};
}