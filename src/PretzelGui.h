//
//  Header.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"

#include "PretzelGlobal.h"
#include "BasePretzel.h"
#include "PretzelRow.h"

//
#include "PretzelLabel.h"
#include "PretzelSlider.h"
#include "PretzelSaveLoad.h"
#include "PretzelButton.h"
#include "PretzelToggle.h"
namespace Pretzel{
	class PretzelGui : public PretzelRow {
	public:
		PretzelGui(std::string title = "");
		PretzelGui(std::string title, int width, int height);
		PretzelGui(std::string title, PretzelFillStyle width, PretzelFillStyle height);

		void draw();
		void setSize(ci::Vec2i size);
		void setPos(const ci::Vec2i &pos);
		void minimize(bool doMinimize = true);

		void saveSettings(ci::fs::path settingsPath = ci::fs::path());
		void loadSettings(ci::fs::path settingsPath = ci::fs::path());

		// ------------------
		void addLabel(std::string labelText);
		void addSlider(std::string label, float *variable, float min, float max);
		void addSlider(std::string label, int *variable, int min, int max);
		void addSaveLoad();
		void addToggle(std::string label, bool *value);

		template<typename T, typename Y>
		inline void addButton(std::string labelText, T callback, Y *callbackObject){
			PretzelButton *newButton = new PretzelButton(this, labelText);
			newButton->signalOnPress.connect(std::bind(callback, callbackObject));
		}

	private:
		void init(std::string title = "");

		// mouse events
		boost::signals2::scoped_connection  mMouseBeganCallBack,
			mMouseDragCallBack,
			mMouseEndCallBack,
			mMouseMovedCallBack;

		virtual void onMouseDown(ci::app::MouseEvent &event);
		virtual void onMouseDragged(ci::app::MouseEvent &event);
		virtual void onMouseUp(ci::app::MouseEvent &event);
		virtual void onMouseMoved(ci::app::MouseEvent &event);

		ci::Vec2i		mPos;

		ci::Surface32f  mSkin;
		ci::gl::Texture mTex;

		PretzelLabel	*mDefaultLabel;
		bool			bDragging;
		bool			bResizing;

		ci::Vec2f		mMouseOffset;
		ci::Vec2f		mResizeStartSize;

		ci::Rectf		mResizeRect;

		double			mLastClickTime;
		bool			bDrawMinimized;
	};
}