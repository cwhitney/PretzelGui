//
//  PanelGlobal.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/21/14.
//
//

#include "PanelGlobal.h"

namespace Panel {

	PanelGlobal* PanelGlobal::mInstance = NULL;
	enum {
		PANEL_FONT_ALIGN_LEFT,
		PANEL_FONT_ALIGN_RIGHT,
		PANEL_FONT_ALIGN_CENTER
	};

	PanelGlobal * PanelGlobal::getInstance(){
		if (!mInstance){
			mInstance = new PanelGlobal();
		}
		return mInstance;
	}

	void PanelGlobal::renderTextInternal(std::string text, ci::Vec2i pos, int align){
		if (!guiFont){
#ifdef _WIN32
			ci::Font tmp("Arial", 12);
#else
			ci::Font tmp("Arial", 12);
#endif
			guiFont = ci::gl::TextureFont::create(tmp);
		}

		ci::gl::TextureFont::DrawOptions opts;
		opts.pixelSnap(true);

		ci::Vec2f textSize = guiFont->measureString(text);

		ci::gl::pushMatrices(); {
			ci::gl::translate(pos);
			ci::gl::translate(0, (int)textSize.y);

			if (align == PANEL_FONT_ALIGN_RIGHT){
				ci::gl::translate(-textSize.x, 0);
			}
			else if (align == PANEL_FONT_ALIGN_CENTER){
				ci::gl::translate((int)textSize.x*-0.5, 0);
			}

			ci::gl::color(P_TEXT_COLOR);
			guiFont->drawString(text, ci::Vec2f::zero(), opts);
		}ci::gl::popMatrices();
	}

	void PanelGlobal::renderText(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, PANEL_FONT_ALIGN_LEFT);
	}

	void PanelGlobal::renderTextRight(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, PANEL_FONT_ALIGN_LEFT);
	}

	void PanelGlobal::renderTextCentered(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, PANEL_FONT_ALIGN_CENTER);
	}

}
