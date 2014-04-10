//
//  PretzelGlobal.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/21/14.
//
//

#include "PretzelGlobal.h"

namespace Pretzel {
	PretzelGlobal* PretzelGlobal::mInstance = NULL;
	enum {
		Pretzel_FONT_ALIGN_LEFT,
		Pretzel_FONT_ALIGN_RIGHT,
		Pretzel_FONT_ALIGN_CENTER
	};

	PretzelGlobal * PretzelGlobal::getInstance(){
		if (!mInstance){
			mInstance = new PretzelGlobal();
		}
		return mInstance;
	}

	void PretzelGlobal::renderTextInternal(std::string text, ci::Vec2i pos, int align){
		if (!guiFont){
#ifdef _WIN32
			ci::Font tmp("Arial", 16);
#else
			ci::Font tmp("Arial", 12);
#endif
			guiFont = ci::gl::TextureFont::create(tmp);
			emHeight = guiFont->measureString("M").y;
		}

		ci::gl::TextureFont::DrawOptions opts;
		opts.pixelSnap(true);

		ci::Vec2f textSize = guiFont->measureString(text);

		ci::gl::pushMatrices(); {
			ci::gl::translate(pos);
			ci::gl::translate(0, (int)emHeight);

			ci::gl::color(P_TEXT_COLOR);

			if (align == Pretzel_FONT_ALIGN_RIGHT){
				guiFont->drawString(text, ci::Vec2i(-textSize.x, 0), opts);
			}
			else if (align == Pretzel_FONT_ALIGN_CENTER){
				guiFont->drawString(text, ci::Vec2i((int)textSize.x*-0.5, 0), opts);
			}
			else{
				guiFont->drawString(text, ci::Vec2i::zero(), opts);
			}
		}ci::gl::popMatrices();
	}

	void PretzelGlobal::renderText(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, Pretzel_FONT_ALIGN_LEFT);
	}

	void PretzelGlobal::renderTextRight(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, Pretzel_FONT_ALIGN_RIGHT);
	}

	void PretzelGlobal::renderTextCentered(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, Pretzel_FONT_ALIGN_CENTER);
	}

}
