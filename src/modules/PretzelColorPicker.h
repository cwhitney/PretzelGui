//
//  PretzelColorPicker.h
//  BasicSample
//
//  Created by Charlie Whitney on 6/30/14.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/Timeline.h"
#include "cinder/ip/Fill.h"

#include "components/BasePretzel.h"
#include "modules/PretzelShaders.h"

namespace pretzel {
    
	class PretzelColorPicker : public BasePretzel {
	  public:
		PretzelColorPicker(BasePretzel *parent, std::string label, ci::Color    *value);
		PretzelColorPicker(BasePretzel *parent, std::string label, ci::ColorA   *value);
        
        void update() override;
        void draw() override;
		void updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) override;
        
		void mouseDown(const ci::vec2 &pos) override;
        void mouseDragged(const ci::vec2 &pos) override;
        void mouseUp(const ci::vec2 &pos) override;
        void mouseMoved(const ci::vec2 &pos) override;
        
      private:
        void setup();
        void expand();
        void contract();
        
        void redrawHueBox();
        void getCrosshairPosFromCol();
        ci::ColorA getColorAtPos( ci::vec2 crosshairPos );
        
		ci::Color           *mColor;
        ci::ColorA          *mColorA;
        ci::ColorA          mLastColor;
        
        ci::ColorA          mHueCol;
        
		std::string         mLabel;
        
        ci::Rectf           mCollapsedRect;
        ci::Rectf           mExpandedRect;
        
        ci::Rectf           mColorPickRect;
        ci::Rectf           mColorSwatchRect;
        ci::Rectf           mHueStripRect;
        
        ci::gl::TextureRef  mArrowTex;
        ci::gl::TextureRef  mCrosshairTex;
        ci::gl::TextureRef  mCheckerPat;
        
        ci::Surface         mHueSurf;
        ci::gl::TextureRef  mHueStrip;
        
        
        ci::vec2            mCrosshairPos;
        
        bool                bHover;
        bool                bUseAlpha;
        bool                bExpanded;
        bool                bDragging;
        bool                bDraggingHue;
        
        ci::Anim<float>     mArrowRotation;
        
        // ---
        ci::gl::GlslProgRef mBoxShader;
        ci::gl::FboRef      mBoxFbo;
        float               mHueNorm;
        
	};
}
