//
//  PretzelColorPicker.h
//  BasicSample
//
//  Created by Charlie Whitney on 6/30/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "BasePretzel.h"

namespace Pretzel {
    
    template<typename T>
	class PretzelColorPicker : public BasePretzel {
	public:
		PretzelColorPicker(BasePretzel *parent, std::string label, ci::Color    *value);
		PretzelColorPicker(BasePretzel *parent, std::string label, ci::ColorA   *value);
        
		virtual void draw();
		void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);
        
//		virtual void mouseDown(const ci::Vec2i &pos);
//        virtual void mouseDragged(const ci::Vec2i &pos);
//        virtual void mouseUp(const ci::Vec2i &pos);
//        virtual void mouseMoved(const ci::Vec2i &pos);
        
	private:
//        union {
//            ci::Color c,
//            ci::ColorA cc
//        } colTypes;
//        
//		ci::ColorT<T>       *mColor;
//		std::string         mLabel;
//        
//        bool                bHover;
	};
    
}
