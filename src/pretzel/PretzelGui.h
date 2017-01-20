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
#include "cinder/ImageIo.h"
#include "Resources.h"


#include "components/BasePretzel.h"
#include "components/ScrollPane.h"
#include "components/PretzelRow.h"

#include "components/PretzelRoot.h" // <--
#include "pretzel/PretzelGlobal.h"  // <--

#include "modules/PretzelLabel.h"
#include "modules/PretzelSlider.h"
#include "modules/PretzelSaveLoad.h"
#include "modules/PretzelButton.h"
#include "modules/PretzelToggle.h"
#include "modules/PretzelTextField.h"
#include "modules/PretzelColorPicker.h"
#include "modules/PretzelEnum.h"

#include "components/WindowSystem.h"

namespace pretzel
{    
    using PretzelGuiRef = std::shared_ptr<class PretzelGui>;
    using PretzelRootRef = std::shared_ptr<class PretzelRoot>;
    class PWindowData;
    
	class PretzelGui : public ScrollPane
    {
	  public:
		PretzelGui(std::string title, int width, int height, ci::app::WindowRef window=ci::app::getWindow());
        ~PretzelGui();
        
        static PretzelGuiRef create(std::string title = "");
        static PretzelGuiRef create(std::string title, int width, int height, ci::app::WindowRef window=ci::app::getWindowIndex(0) );
        static void drawAll();
        
		void draw() override;
        void mouseDown(const ci::vec2 &pos) override;
        void mouseDragged(const ci::vec2 &pos) override;
        void mouseUp(const ci::vec2 &pos) override;
        void mouseMoved(const ci::vec2 &pos) override;
        void mouseWheel(const float increment) override;
        void keyDown(const char &key, const int &keyCode) override;
        
		void setSize(ci::vec2 size);
		void setPos(const ci::vec2 &pos);
		void minimize(bool doMinimize = true);
		void setVisible(bool visible);
		void toggleVisible();
		bool isVisible();
        
        ci::Rectf getBounds() override;
        ci::Rectf getGlobalBounds() override;

		void saveSettings(ci::fs::path settingsPath = ci::fs::path());
		void loadSettings(ci::fs::path settingsPath = ci::fs::path());

		// ------------------
		PretzelLabel*   	addLabel(std::string labelText);
		PretzelSlider*      addSlider(std::string label, float *variable, float min, float max);
		PretzelSlider*      addSlider(std::string label, int *variable, int min, int max);
        PretzelSlider*      addSlider(std::string label, ci::vec2 *variable, ci::vec2 min, ci::vec2 max);
        PretzelSlider*      addSlider(std::string label, ci::vec3 *variable, ci::vec3 min, ci::vec3 max);
        PretzelSaveLoad*    addSaveLoad();
		PretzelToggle*      addToggle(std::string label, bool *value);
		PretzelTextField*   addTextField(std::string label, std::string *variable, bool editable = true);
        PretzelEnum*        addEnum(std::string label, std::vector<std::string> *strList, int *num);
        
        PretzelColorPicker* addColorPicker(std::string label, ci::Color *color);
        PretzelColorPicker* addColorPicker(std::string label, ci::ColorA *color);
        
		template<typename T, typename Y>
		inline void addButton(std::string labelText, T callback, Y *callbackObject){
			PretzelButton *newButton = new PretzelButton(this, labelText);
			newButton->mConnection = newButton->signalOnPress.connect(std::bind(callback, callbackObject));
            mWidgetList.push_back( newButton );
		}

	  private:
		void init(std::string title = "");
        void onSettingsLoaded();
        
//        PretzelRootRef              mPretzelRoot;
        std::vector<BasePretzel*>   mWidgetList;

        ci::app::WindowRef  mWindowRef;
		PretzelLabel        *mDefaultLabel;
        
		bool                bVisible        = true;
		bool                bDragging       = false;
		bool                bResizing       = false;
        bool                bDrawMinimized  = false;
        bool                bChangedCursor  = false;

		ci::vec2            mMouseOffset;
		ci::vec2            mResizeStartSize;
		ci::Rectf           mResizeRect;

		double              mLastClickTime = 0.0f;
	};
}
