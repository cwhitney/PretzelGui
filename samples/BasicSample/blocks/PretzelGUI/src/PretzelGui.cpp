//
//  Header.h
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace Pretzel;

PretzelGui::PretzelGui(std::string title) : PretzelRow(NULL, 300, 500) { init(title); }
PretzelGui::PretzelGui(std::string title, int width, int height) : PretzelRow(NULL, width, height){ init(title); }
PretzelGui::PretzelGui(std::string title, PretzelFillStyle width, PretzelFillStyle height) : PretzelRow(NULL, width, height){ init(title); }

void PretzelGui::init( std::string title ){
	bDragging = false;
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
	
	mMouseBeganCallBack = window->getSignalMouseDown().connect(std::bind(&PretzelGui::onMouseDown, this, std::placeholders::_1));
	mMouseMovedCallBack = window->getSignalMouseDrag().connect(std::bind(&PretzelGui::onMouseDragged, this, std::placeholders::_1));
	mMouseEndCallBack = window->getSignalMouseUp().connect(std::bind(&PretzelGui::onMouseUp, this, std::placeholders::_1));
	
	mPos.set(10, 10);

	mGlobal->renderText("");	// initialize the font

	if (title == ""){
		title = "Settings";
	}
	defaultLabel = new PretzelLabel(this, title);
}

// ---------------------------------------------------------
void PretzelGui::onMouseDown(ci::app::MouseEvent &event){
	if (defaultLabel->getBounds().contains(event.getPos() - mPos)){
		bDragging = true;
		mDragOffset = event.getPos() - mPos;
	}else{
		mouseDown(event.getPos() - mPos);
	}
}

void PretzelGui::onMouseDragged(ci::app::MouseEvent &event){
	if (bDragging){
		mPos = event.getPos() - mDragOffset;
	}else{
		mouseDragged(event.getPos() - mPos);
	}
}

void PretzelGui::onMouseUp(ci::app::MouseEvent &event){
	if (bDragging){
		bDragging = false;
	}else{
		mouseUp(event.getPos() - mPos);
	}
}

// ---------------------------------------------------------
void PretzelGui::draw(){
	glDisable(GL_MULTISAMPLE);

	gl::enableAlphaBlending();
	gl::color(Color(1, 1, 1));

	gl::pushMatrices(); {
		gl::translate(mPos);
		PretzelRow::draw();

		gl::color(mGlobal->P_GUI_BORDER);
		gl::drawStrokedRect(mBounds);
	}gl::popMatrices();

	glEnable(GL_MULTISAMPLE);
}

// --------------------------------------------------
void PretzelGui::addLabel(std::string labelText){
	new PretzelLabel(this, labelText);
}

void PretzelGui::addSlider(std::string label, float *variable, float min, float max){
	new PretzelSlider(this, label, variable, min, max);
}

void PretzelGui::addSaveLoad() {
	new PretzelSaveLoad(this);
}

void PretzelGui::addToggle(std::string label, bool *value){
	new PretzelToggle(this, label, value);
}