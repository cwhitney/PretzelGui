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
#include "cinder/Json.h"
#include <boost/signals2.hpp>

namespace Pretzel {

    enum CursorType {
        ARROW = 0,
        IBEAM,
        HAND,
        RESIZE_RL
    };
    
    enum FontAlignment {
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_CENTER
	};
    
    enum WidgetType {
        UNINITALIZED = 0,
        BUTTON,
        LABEL,
        SAVELOAD,
        SLIDER,
        TEXTFIELD,
        TOGGLE
    };
    
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
		ci::ColorA P_HOVER_COLOR;
        ci::ColorA P_ACTIVE_COLOR;

		ci::gl::TextureFontRef  guiFont;
		ci::gl::TextureRef		mSkinTex;
        
        boost::signals2::signal<void(void)>	signalOnSettingsSave;
        boost::signals2::signal<void(void)>	signalOnSettingsLoad;

		void renderText(const std::string text, ci::Vec2i pos = ci::Vec2i::zero());
		void renderTextRight(const std::string text, ci::Vec2i pos = ci::Vec2i::zero());
		void renderTextCentered(const std::string text, ci::Vec2i pos = ci::Vec2i::zero());

		void saveSettings(const ci::fs::path settingsPath = ci::fs::path() );
		void loadSettings(const ci::fs::path settingsPath = ci::fs::path() );

		void addSaveParam(const std::string name, float *val);
		void addSaveParam(const std::string name, int *val);
		void addSaveParam(const std::string name, bool *val);
		void addSaveParam(const std::string name, std::string *val);
        void addSaveParam(const std::string name, ci::Vec2f *val);
        void addSaveParam(const std::string name, ci::Vec3f *val);

		template <typename T>
		std::string to_string_with_precision(const T num, const int n = 2) {
			std::ostringstream out;
			out << std::fixed << std::setprecision(n) << num;
			return out.str();
		}
        
        void setCursor( CursorType type );

	private:
		enum PretzelTypes {
			_FLOAT,
			_INT,
			_BOOL,
			_STRING,
            _VEC2F,
            _VEC3F
		};

		struct PretzelParam{
			std::string name;
			void* value;
			PretzelTypes type;
		};

		// PRIVATE CONSTRUCTOR + COPY
		PretzelGlobal(){};
		PretzelGlobal(PretzelGlobal const&){};
		static PretzelGlobal		*mInstance;

		// PARAMS
		void addParamInternal(std::string name, void* value, PretzelTypes type);
		std::vector<PretzelParam>	mParamList;

		// TEXT
		void renderTextInternal(std::string text, ci::Vec2i pos, int align);
		int	emHeight;
	};
}
