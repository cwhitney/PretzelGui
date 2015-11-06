//
//  PretzelColorPicker.h
//  BasicSample
//
//  Created by Charlie Whitney on 6/30/14.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/Texture.h"
#include "cinder/Timeline.h"
#include "cinder/ip/Fill.h"

#include "components/BasePretzel.h"

namespace pretzel {
    
	class PretzelColorPicker : public BasePretzel {
	  public:
		PretzelColorPicker(BasePretzel *parent, std::string label, ci::Color    *value);
		PretzelColorPicker(BasePretzel *parent, std::string label, ci::ColorA   *value);
        
      
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
        
        ci::vec2           mCrosshairPos;
        
        bool                bHover;
        bool                bUseAlpha;
        bool                bExpanded;
        bool                bDragging;
        
        ci::Anim<float>     mArrowRotation;
	};
}
