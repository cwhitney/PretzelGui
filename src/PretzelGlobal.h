//
//  PretzelGlobal.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/20/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/Gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"

namespace Pretzel {

	class PretzelGlobal {
	public:
		static PretzelGlobal* getInstance();

		ci::ColorA P_GUI_BORDER;
		ci::ColorA P_BG_COLOR;
		ci::ColorA P_TAB_COLOR;
		ci::ColorA P_TEXT_COLOR;
		ci::ColorA P_OUTLINE_COLOR;
		ci::ColorA P_HIGHLIGHT_COLOR;
		ci::ColorA P_SLIDER_COLOR;

		ci::gl::TextureFontRef guiFont;

		ci::gl::TextureRef		mSkinTex;

		void renderText(std::string text, ci::Vec2i pos = ci::Vec2i::zero());
		void renderTextRight(std::string text, ci::Vec2i pos = ci::Vec2i::zero());
		void renderTextCentered(std::string text, ci::Vec2i pos = ci::Vec2i::zero());

		void saveSettings();
		void loadSettings();

		template <typename T>
		std::string to_string_with_precision(const T num, const int n = 2) {
			std::ostringstream out;
			out << fixed << std::setprecision(n) << num;
			return out.str();
		}

	private:
		PretzelGlobal(){};
		PretzelGlobal(PretzelGlobal const&){};
		static PretzelGlobal		*mInstance;

		void renderTextInternal(std::string text, ci::Vec2i pos, int align);
		float	emHeight;
	};
}
