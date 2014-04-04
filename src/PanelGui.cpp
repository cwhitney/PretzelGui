//
//  Header.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "PanelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace Panel;

PanelGui::PanelGui() : PanelRow(NULL, 300, 500) {}
PanelGui::PanelGui(int width, int height) : PanelRow(NULL, width, height){}
PanelGui::PanelGui(PanelFillStyle width, PanelFillStyle height) : PanelRow(NULL, width, height){}

void PanelGui::setup() {
	bDragging = false;

    init();
}

void PanelGui::init(){
    mSkin = Surface32f( loadImage( ci::app::loadAsset("../../../assets/default_skin.png") ) );
    mTex = gl::Texture( mSkin );

	mGlobal->P_GUI_BORDER.set(mSkin.getPixel(ci::Vec2i(10, 380)));
	mGlobal->P_BG_COLOR.set(mSkin.getPixel(ci::Vec2i(10, 400)));
	mGlobal->P_TAB_COLOR.set(mSkin.getPixel(ci::Vec2i(10, 420)));
	mGlobal->P_TEXT_COLOR.set(mSkin.getPixel(ci::Vec2i(10, 440)));
	mGlobal->P_OUTLINE_COLOR.set(mSkin.getPixel(ci::Vec2i(10, 460)));
	mGlobal->P_HIGHLIGHT_COLOR.set(mSkin.getPixel(ci::Vec2i(10, 480)));
	mGlobal->P_SLIDER_COLOR.set(mSkin.getPixel(ci::Vec2i(10, 500)));

	ci::app::WindowRef window = cinder::app::getWindow();
	
	mMouseBeganCallBack = window->getSignalMouseDown().connect(std::bind(&PanelGui::onMouseDown, this, std::placeholders::_1));
	mMouseMovedCallBack = window->getSignalMouseDrag().connect(std::bind(&PanelGui::onMouseDragged, this, std::placeholders::_1));
	mMouseEndCallBack = window->getSignalMouseUp().connect(std::bind(&PanelGui::onMouseUp, this, std::placeholders::_1));
	
	mPos.set(10, 10);

	mGlobal->renderText("");	// initialize the font

	defaultLabel = new PanelLabel(this, "Settings");
}

// ---------------------------------------------------------
void PanelGui::onMouseDown(ci::app::MouseEvent &event){
	if (defaultLabel->getBounds().contains(event.getPos() - mPos)){
		bDragging = true;
		mDragOffset = event.getPos() - mPos;
	}else{
		mouseDown(event.getPos() - mPos);
	}
}

void PanelGui::onMouseDragged(ci::app::MouseEvent &event){
	if (bDragging){
		mPos = event.getPos() - mDragOffset;
	}else{
		mouseDragged(event.getPos() - mPos);
	}
}

void PanelGui::onMouseUp(ci::app::MouseEvent &event){
	if (bDragging){
		bDragging = false;
	}else{
		mouseUp(event.getPos() - mPos);
	}
}

// ---------------------------------------------------------
void PanelGui::draw(){
	glDisable(GL_MULTISAMPLE);

	gl::enableAlphaBlending();
	gl::color(Color(1, 1, 1));

	gl::pushMatrices(); {
		gl::translate(mPos);
		PanelRow::draw();

		gl::color(mGlobal->P_GUI_BORDER);
		gl::drawStrokedRect(mBounds);
	}gl::popMatrices();

	glEnable(GL_MULTISAMPLE);
}

// --------------------------------------------------
void PanelGui::addLabel(std::string labelText){
	new PanelLabel(this, labelText);
}

void PanelGui::addSlider(std::string label, float *variable, float min, float max){
	new PanelSlider(this, label, variable, min, max);
}

void PanelGui::addSaveLoad() {
	new PanelSaveLoad(this);
}

void PanelGui::addToggle(std::string label, bool *value){
	new PanelToggle(this, label, value);
}