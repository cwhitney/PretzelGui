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

#include "PanelGlobal.h"
#include "BasePanel.h"
#include "PanelRow.h"

//
#include "PanelLabel.h"
#include "PanelSlider.h"
#include "PanelSaveLoad.h"
#include "PanelButton.h"
#include "PanelToggle.h"

class PanelGui : public PanelRow {
  public:
    PanelGui();
	PanelGui(int width, int height);
    PanelGui( PanelFillStyle width, PanelFillStyle height );
    
    void setup();
    void draw();
	
	void setSize( ci::Vec2f size ){
		mBounds.x2 = size.x;
		mBounds.y2 = size.y;

		//updateBounds(Vec2f::zero(), mBounds);
		updateChildrenBounds();
	}

	// ------------------
	void addLabel( std::string labelText );
	void addSlider(std::string label, float *variable, float min, float max);
	void addSaveLoad();
	void addToggle( std::string label, bool *value);

	template<typename T, typename Y>
	inline void addButton(std::string labelText, T callback, Y *callbackObject){
		PanelButton *newButton = new PanelButton(this, labelText);

		//PanelButton *newButton = new PanelButton(this, labelText);
		newButton->signalOnPress.connect(std::bind(callback, callbackObject));

		cinder::app::console() << "adding a button" << std::endl;
	}

  private:
    void init();

	// mouse events
	boost::signals2::scoped_connection  mMouseBeganCallBack,
										mMouseMovedCallBack,
										mMouseEndCallBack;

	virtual void onMouseDown(ci::app::MouseEvent &event);
	virtual void onMouseDragged(ci::app::MouseEvent &event);
	virtual void onMouseUp(ci::app::MouseEvent &event);

	ci::Vec2i		mPos;

    ci::Surface32f  mSkin;
    ci::gl::Texture mTex;


	PanelLabel	*defaultLabel;
	bool		bDragging;
	ci::Vec2f	mDragOffset;
};