//
//  PretzelGlobal.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/20/14.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Json.h"
#include "cinder/ImageIo.h"
#include "cinder/Log.h"

#if defined( CINDER_MSW )
    #include <Windows.h>
#endif

#include "Resources.h"


namespace pretzel
{
    enum CursorType {
        ARROW = 0,
        IBEAM,
        HAND,
        RESIZE_RL
    };
    
    enum FontAlignment {
		ALIGN_LEFT = 0,
		ALIGN_RIGHT,
		ALIGN_CENTER
	};
    
    enum WidgetType {
        UNINITALIZED = 0,
        ROOT,
        GUI,
        BUTTON,
        LABEL,
        SAVELOAD,
        SLIDER,
        TEXTFIELD,
        TOGGLE,
        COLOR_PICKER,
        ENUM
    };

    
    // ------------------------------------------------
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
        ci::Surface             mSkinSurf;
		ci::gl::TextureRef		mSkinTex;
        
        ci::signals::Signal<void(void)>	signalOnSettingsSave;
		ci::signals::Signal<void(void)>	signalOnSettingsLoad;

		void renderText(const std::string text, ci::vec2 pos = ci::vec2(0,0));
		void renderTextRight(const std::string text, ci::vec2 pos = ci::vec2(0,0));
		void renderTextCentered(const std::string text, ci::vec2 pos = ci::vec2(0,0));

		void saveSettings(const ci::fs::path settingsPath = ci::fs::path() );
		void loadSettings(const ci::fs::path settingsPath = ci::fs::path() );

		void addSaveParam(const std::string name, float *val);
		void addSaveParam(const std::string name, int *val);
		void addSaveParam(const std::string name, bool *val);
		void addSaveParam(const std::string name, std::string *val);
        void addSaveParam(const std::string name, ci::vec2 *val);
        void addSaveParam(const std::string name, ci::vec3 *val);
        void addSaveParam(const std::string name, ci::Color *val);
        void addSaveParam(const std::string name, ci::ColorA *val);

		template <typename T>
		std::string to_string_with_precision(const T num, const int n = 2) {
			std::ostringstream out;
			out << std::fixed << std::setprecision(n) << num;
			return out.str();
		}
        
        void setCursor( CursorType type );
        ci::gl::TextureRef  getTextureFromSkin( ci::Rectf rect );
        
//        void setGlobalPos( const ci::vec2 &pos ){ mGlobalPos = pos; };
        //const ci::vec2 getGlobalPos(){ return mGlobalPos; };
        
//        void drawSolidRect( ci::Rectf rect );
//        void drawStrokedRect( ci::Rectf rect );
//        void drawLine( ci::vec2 start, ci::vec2 end );

	private:
        void setup();
		
        enum PretzelTypes {
			_FLOAT,
			_INT,
			_BOOL,
			_STRING,
            _VEC2,
            _VEC3,
            _COLOR,
            _COLORA
        };

		struct PretzelParam {
			std::string name;
			void* value;
			PretzelTypes type;
		};

#if defined( CINDER_MSW )
		HCURSOR mCursorArrow, mCursorIBeam, mCursorHand, mCursorResize;
#endif 
            
        ci::vec2   mGlobalPos;

		// PRIVATE CONSTRUCTOR + COPY
		PretzelGlobal(){};
		PretzelGlobal(PretzelGlobal const&){};
		static PretzelGlobal		*mInstance;

		// PARAMS
		void addParamInternal(std::string name, void* value, PretzelTypes type);
		std::vector<PretzelParam>	mParamList;

		// TEXT
        void renderTextInternal(std::string text, ci::vec2 pos, int align);
		int	emHeight;
        
        // DRAWING
//        ci::gl::VertBatch   mRectVerts, mStrokedRectVerts, mLineVerts;
//        ci::gl::BatchRef mSolidRectBatch, mStrokedRectBatch, mLineBatch;
    };
    
    // pretzel namespace
    inline pretzel::PretzelGlobal*	pretzel()	{ return PretzelGlobal::getInstance(); }
}
