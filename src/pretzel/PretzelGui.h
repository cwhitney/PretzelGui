//
//  Header.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

#include "pretzel/PretzelGlobal.h"

#include "components/BasePretzel.h"
#include "components/ScrollPane.h"
#include "components/PretzelRow.h"

#include "modules/PretzelLabel.h"
#include "modules/PretzelSlider.h"
#include "modules/PretzelSaveLoad.h"
#include "modules/PretzelButton.h"
#include "modules/PretzelToggle.h"
#include "modules/PretzelTextField.h"
#include "modules/PretzelColorPicker.h"

namespace Pretzel{
    class PretzelGui;
    typedef std::shared_ptr<PretzelGui> PretzelGuiRef;
    
	class PretzelGui : public ScrollPane {
	  public:
		PretzelGui(std::string title = "");
		PretzelGui(std::string title, int width, int height);
        ~PretzelGui();
        
        static PretzelGuiRef create(std::string title = ""){ return std::make_shared<PretzelGui>(title); }
        static PretzelGuiRef create(std::string title, int width, int height){ return std::make_shared<PretzelGui>(title, width,height); }
        
		void draw();
		void setSize(ci::vec2 size);
		void setPos(const ci::vec2 &pos);
		void minimize(bool doMinimize = true);
		void setVisible(bool visible);
		void toggleVisible();
		bool isVisible();

		void saveSettings(ci::fs::path settingsPath = ci::fs::path());
		void loadSettings(ci::fs::path settingsPath = ci::fs::path());

		// ------------------
		void addLabel(std::string labelText);
		void addSlider(std::string label, float *variable, float min, float max);
		void addSlider(std::string label, int *variable, int min, int max);
        void addSlider(std::string label, ci::vec2 *variable, ci::vec2 min, ci::vec2 max);
        void addSlider(std::string label, ci::vec3 *variable, ci::vec3 min, ci::vec3 max);
        void addSaveLoad();
		void addToggle(std::string label, bool *value);
		void addTextField(std::string label, std::string *variable, bool editable = true);
        
        void addColorPicker(std::string label, ci::Color *color);
        void addColorPicker(std::string label, ci::ColorA *color);
        
		template<typename T, typename Y>
		inline void addButton(std::string labelText, T callback, Y *callbackObject){
			PretzelButton *newButton = new PretzelButton(this, labelText);
			newButton->mConnection = newButton->signalOnPress.connect(std::bind(callback, callbackObject));
            
            mWidgetList.push_back( newButton );
		}

	  private:
		void init(std::string title = "");
        void connectSignals();
        void disconnectSignals();
        void onSettingsLoaded();

		// mouse events
        ci::signals::Connection  mMouseBeganCallBack,
			mMouseDragCallBack,
			mMouseEndCallBack,
			mMouseMovedCallBack,
			mKeyDownCallback;

		virtual void onMouseDown(ci::app::MouseEvent &event);
		virtual void onMouseDragged(ci::app::MouseEvent &event);
		virtual void onMouseUp(ci::app::MouseEvent &event);
		virtual void onMouseMoved(ci::app::MouseEvent &event);
		virtual void onKeyDown(ci::app::KeyEvent &event);
        
        std::vector<BasePretzel*>    mWidgetList;

		PretzelLabel	*mDefaultLabel;
		bool			bVisible;
		bool			bDragging;
		bool			bResizing;

		ci::vec2		mMouseOffset;
		ci::vec2		mResizeStartSize;

		ci::Rectf		mResizeRect;

		double			mLastClickTime;
		bool			bDrawMinimized;
        bool            bChangedCursor;
	};
}