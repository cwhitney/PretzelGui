#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"

namespace pretzel
{
	class PretzelSaveLoad : public BasePretzel
    {
	  public:
		PretzelSaveLoad(BasePretzel *parent);
		PretzelSaveLoad(BasePretzel *parent, ci::fs::path savePath);

      
		void draw() override;
		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) override;

		void mouseDown(const ci::vec2 &pos) override;
		void mouseMoved(const ci::vec2 &pos) override;
        void mouseUp(const ci::vec2 &pos) override;
      private:  
	  
		ci::fs::path	mSavePath;
		ci::Rectf		mSaveRect, mLoadRect;
		bool			bHoverSave, bHoverLoad;
        
        ci::Color       mSaveBg, mLoadBg;
	};
}
