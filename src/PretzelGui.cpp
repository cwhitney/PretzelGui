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
	bResizing = false;
	bDrawMinimized = false;
    mSkin = Surface32f( loadImage( ci::app::loadAsset("default_skin.png") ) );
    mTex = gl::Texture( mSkin );

	mLastClickTime = 0.0;

	mGlobal->mSkinTex = gl::Texture::create(mSkin);

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

	Vec2i ul = mBounds.getSize() - Vec2i(10, 10);
	Vec2i lr = mBounds.getSize();
	mResizeRect.set( ul.x, ul.y, lr.x, lr.y );

	mGlobal->renderText("");	// initialize the font

	if (title == ""){
		title = "Settings";
	}
	mDefaultLabel = new PretzelLabel(this, title);
}

void PretzelGui::setSize(Vec2i size){
	int minWidth = 150;
	int minHeight = 150;

	mBounds.x2 = max(size.x, minWidth);
	mBounds.y2 = max(size.y, minHeight);

	updateChildrenBounds();

	Vec2i ul = mBounds.getSize() - Vec2i(10, 10);
	Vec2i lr = mBounds.getSize();
	mResizeRect.set(ul.x, ul.y, lr.x, lr.y);
}

void PretzelGui::minimize(bool doMinimize){
	bDrawMinimized = doMinimize;
}

// ---------------------------------------------------------
void PretzelGui::onMouseDown(ci::app::MouseEvent &event){

	if (mDefaultLabel->getBounds().contains(event.getPos() - mPos)){	
		
		if (getElapsedSeconds() - mLastClickTime < 0.25){	// Double click title bar, minimize
			bDrawMinimized = !bDrawMinimized;
		}else{												// Single click title bar, drag
			bDragging = true;
			mMouseOffset = event.getPos() - mPos;
		}
		mLastClickTime = getElapsedSeconds();
	}
	else if (bDrawMinimized){								// We are minimized, don't go further
		return;
	}
	else if ( mResizeRect.contains(event.getPos() - mPos)){	// Hit in lower right corner for resize
		bResizing = true;
		mResizeStartSize = mBounds.getSize();
		mMouseOffset = event.getPos() - mPos;
	}else{
		mouseDown(event.getPos() - mPos);					// Propagate to children
	}
}

void PretzelGui::onMouseDragged(ci::app::MouseEvent &event){
	if (bDragging){
		mPos = event.getPos() - mMouseOffset;
	}else if (bResizing){
		Vec2i newSize = mResizeStartSize + event.getPos() - mMouseOffset;
		setSize(newSize);
	}else{
		mouseDragged(event.getPos() - mPos);
	}
}

void PretzelGui::onMouseUp(ci::app::MouseEvent &event){
	if (bDragging){
		bDragging = false;
	}else if (bResizing){
		bResizing = false;
	}else{
		mouseUp(event.getPos() - mPos);
	}
}

// ---------------------------------------------------------
void PretzelGui::draw(){

	// grab some gl settings
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glDisable(GL_MULTISAMPLE);
	float curCol[4];
	glGetFloatv(GL_CURRENT_COLOR, curCol);

	GLboolean bDepthtestEnable;
	glGetBooleanv(GL_DEPTH_TEST, &bDepthtestEnable);
	gl::disableDepthRead();

	

	// -----------------------------------------------------------
	gl::enableAlphaBlending();
	gl::color(Color(1, 1, 1));

	if (bDrawMinimized){
		gl::pushMatrices(); {
			gl::translate(mPos);
			mDefaultLabel->draw();

			gl::color(mGlobal->P_GUI_BORDER);
			gl::drawStrokedRect(mDefaultLabel->getBounds());
		}gl::popMatrices();
	}
	else{
		gl::pushMatrices(); {
			gl::translate(mPos);
			PretzelRow::draw();

			gl::color(mGlobal->P_TAB_COLOR);
			gl::drawSolidRect(Rectf(mBounds.getLowerLeft() - Vec2i(0, 10), mBounds.getLowerRight()));

			gl::color(mGlobal->P_BG_COLOR);
			gl::drawSolidTriangle(mResizeRect.getLowerLeft(), mResizeRect.getUpperRight(), mResizeRect.getLowerRight());

			gl::color(mGlobal->P_GUI_BORDER);
			gl::drawStrokedRect(mBounds);
		}gl::popMatrices();
	}

	// -----------------------------------------------------------
	// reset those gl settings
	glEnable(GL_MULTISAMPLE);
	glColor4f(curCol[0], curCol[1], curCol[2], curCol[3]);
	if (bDepthtestEnable == GL_TRUE){ gl::enableDepthRead(); }

	glPopAttrib();
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