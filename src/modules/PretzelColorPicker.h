//
//  PretzelColorPicker.h
//  BasicSample
//
//  Created by Charlie Whitney on 6/30/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/Texture.h"
#include "cinder/Timeline.h"
#include "cinder/ip/Fill.h"

#include "components/BasePretzel.h"

namespace Pretzel {
    
	class PretzelColorPicker : public BasePretzel {
	public:
		PretzelColorPicker(BasePretzel *parent, std::string label, ci::Color    *value, bool startExpanded=false);
		PretzelColorPicker(BasePretzel *parent, std::string label, ci::ColorA   *value, bool startExpanded=false);
        
		virtual void draw();
		void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);
        
		virtual void mouseDown(const ci::Vec2i &pos);
        virtual void mouseDragged(const ci::Vec2i &pos);
        virtual void mouseUp(const ci::Vec2i &pos);
        virtual void mouseMoved(const ci::Vec2i &pos);
        
	private:
        void setup();
        void expand();
        void contract();
        
		ci::Color           *mColor;
        ci::ColorA          *mColorA;
        
		std::string         mLabel;
        
        ci::Rectf           mCollapsedRect;
        ci::Rectf           mExpandedRect;
        
        ci::Rectf           mColorPickRect;
        ci::Rectf           mColorSwatchRect;
        
        ci::gl::TextureRef  mArrowTex;
        ci::gl::TextureRef  mCrosshairTex;
        ci::Surface         mSwatchSurf;
        ci::gl::TextureRef  mSwatchTex;
        ci::gl::TextureRef  mCheckerPat;
        
        ci::Vec2f           mCrosshairPos;
        
        bool                bHover;
        bool                bUseAlpha;
        bool                bExpanded;
        bool                bDragging;
        
        ci::Anim<float>     mArrowRotation;
	};
}
