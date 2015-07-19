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

namespace Pretzel{
	PretzelGui::PretzelGui(std::string title) : ScrollPane(NULL, 200, 500) { init(title); }
	PretzelGui::PretzelGui(std::string title, int width, int height) : ScrollPane(NULL, width, height){ init(title); }
    //	PretzelGui::PretzelGui(std::string title, PretzelFillStyle width, PretzelFillStyle height) : ScrollPane(NULL, width, height){ init(title); }
    PretzelGui::~PretzelGui(){
        while( mWidgetList.size() ){
            BasePretzel *w = mWidgetList.back();
            
            if( w->type == WidgetType::BUTTON ){
                ((PretzelButton*)w)->mConnection.disconnect();
            }
            mWidgetList.pop_back();
            delete w;
        }
        
        delete mDefaultLabel;
        
        disconnectSignals();
    }
    
    // Initialize the gui with a title
	void PretzelGui::init(std::string title){
		bVisible = true;
		bDragging = false;
		bResizing = false;
		bDrawMinimized = false;
        bChangedCursor = false;
        
		mLastClickTime = 0.0;
        
        mGlobal->P_ACTIVE_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 340)));
		mGlobal->P_HOVER_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 360)));
		mGlobal->P_GUI_BORDER = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 380)));
		mGlobal->P_BG_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 400)));
		mGlobal->P_TAB_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 420)));
		mGlobal->P_TEXT_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 440)));
		mGlobal->P_OUTLINE_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 460)));
		mGlobal->P_HIGHLIGHT_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 480)));
		mGlobal->P_SLIDER_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 500)));
        
		connectSignals();
        mGlobal->signalOnSettingsLoad.connect( std::bind(&PretzelGui::onSettingsLoaded, this) );
        
		mGlobalOffset = vec2(10, 10);
        mGlobal->setGlobalPos( mGlobalOffset );
        
		vec2 ul = mBounds.getSize() - vec2(10, 10);
		vec2 lr = mBounds.getSize();
		mResizeRect.set(ul.x, ul.y, lr.x, lr.y);
        
		mGlobal->renderText("");	// initialize the font
        
		if (title == ""){
			title = "Settings";
		}
		mDefaultLabel = new PretzelLabel(this, title);
	}
    
    // Set the xy dimensions of the gui
	void PretzelGui::setSize(vec2 size){
		float minWidth = 180.f;
		float minHeight = 150.f;
        
        mBounds.x2 = max(size.x, minWidth);
        mBounds.y2 = max(size.y, minHeight);
        
		updateChildrenBounds();
        
		vec2 ul = mBounds.getSize() - vec2(10, 10);
		vec2 lr = mBounds.getSize();
		mResizeRect.set(ul.x, ul.y, lr.x, lr.y);
	}
    
    // Set the xy position of the gui
	void PretzelGui::setPos(const vec2 &pos){
		mGlobalOffset = vec2(pos);
        mGlobal->setGlobalPos( pos );
	}
    
    // Programatically minimize the gui. Same as double-clicking the top bar
	void PretzelGui::minimize(bool doMinimize){
		bDrawMinimized = doMinimize;
	}
    
    // Renders the gui visible/invisible and connects/disconnects all listener signals
	void PretzelGui::setVisible(bool visible){
		bVisible = visible;
        if( bVisible ){ connectSignals();       }
        else{           disconnectSignals();    }
	}
    
    // Toggles the gui visible/invisible and connects/disconnects all listener signals
	void PretzelGui::toggleVisible(){
		bVisible = !bVisible;
        
        if( bVisible ){ connectSignals();       }
        else{           disconnectSignals();    }
	}
    
	bool PretzelGui::isVisible(){
		return bVisible;
	}
    
    void PretzelGui::connectSignals(){
        if( !mMouseBeganCallBack.isConnected() ){
            ci::app::WindowRef window = cinder::app::getWindow();
   
            // uses default priority 0
            mMouseBeganCallBack = window->getSignalMouseDown().connect(std::bind(&PretzelGui::onMouseDown, this, std::placeholders::_1));
            mMouseDragCallBack = window->getSignalMouseDrag().connect(std::bind(&PretzelGui::onMouseDragged, this, std::placeholders::_1));
            mMouseEndCallBack = window->getSignalMouseUp().connect(std::bind(&PretzelGui::onMouseUp, this, std::placeholders::_1));
            mMouseMovedCallBack = window->getSignalMouseMove().connect(std::bind(&PretzelGui::onMouseMoved, this, std::placeholders::_1));
            mKeyDownCallback = window->getSignalKeyDown().connect(std::bind(&PretzelGui::onKeyDown, this, std::placeholders::_1));
        }
    }
    
    void PretzelGui::disconnectSignals(){
        if( mMouseBeganCallBack.isConnected() ){
            mMouseBeganCallBack.disconnect();
            mMouseDragCallBack.disconnect();
            mMouseEndCallBack.disconnect();
            mMouseMovedCallBack.disconnect();
            mKeyDownCallback.disconnect();
        }
    }
    
    void PretzelGui::onSettingsLoaded() {
        updateChildrenBounds();
    }
    
	void PretzelGui::saveSettings(ci::fs::path settingsPath){
		mGlobal->saveSettings(settingsPath);
	}
    
	void PretzelGui::loadSettings(ci::fs::path settingsPath){
		mGlobal->loadSettings(settingsPath);
        updateChildrenBounds();
	}
    
	// ---------------------------------------------------------
	void PretzelGui::onMouseDown(ci::app::MouseEvent &event){
		if (!bVisible) return;
        
		if (mDefaultLabel->getBounds().contains((vec2) event.getPos() - mGlobalOffset)){
            
			if (getElapsedSeconds() - mLastClickTime < 0.25){               // Double click title bar, minimize
				bDrawMinimized = !bDrawMinimized;
			}
			else{                                                           // Single click title bar, drag
				bDragging = true;
				mMouseOffset = ( (vec2) event.getPos() ) - mGlobalOffset;
			}
			mLastClickTime = getElapsedSeconds();
		}
		else if (bDrawMinimized){                                           // We are minimized, don't go further
			return;
		}
		else if (mResizeRect.contains((vec2) event.getPos() - mGlobalOffset)){     // Hit in lower right corner for resize
			bResizing = true;
			mResizeStartSize = mBounds.getSize();
			mMouseOffset = (vec2) event.getPos() - mGlobalOffset;
		}
		else{
			mouseDown((vec2) event.getPos() - mGlobalOffset);                      // Propagate to children
		}
	}
    
	void PretzelGui::onMouseDragged(ci::app::MouseEvent &event){
		if (!bVisible) return;
        
		if (bDragging){
			mGlobalOffset = (vec2) event.getPos() - mMouseOffset;
		}
		else if (bResizing){
			vec2 newSize = mResizeStartSize + (vec2) event.getPos() - mGlobalOffset - mMouseOffset;
			setSize(newSize);
		}
		else{
			mouseDragged((vec2) event.getPos() - mGlobalOffset);
		}
	}
    
	void PretzelGui::onMouseUp(ci::app::MouseEvent &event){
		if (!bVisible) return;
        
		if (bDragging){
			bDragging = false;
		}
		else if (bResizing){
			bResizing = false;
		}
		else{
			mouseUp((vec2) event.getPos() - mGlobalOffset);
		}
	}
    
	void PretzelGui::onMouseMoved(ci::app::MouseEvent &event){
		if (!bVisible) return;
        
        if (mDefaultLabel->getBounds().contains((vec2) event.getPos() - mGlobalOffset)){
            mGlobal->setCursor( CursorType::HAND );
            bChangedCursor = true;
        }else if (mResizeRect.contains((vec2) event.getPos() - mGlobalOffset)){	// Hit in lower right corner for resize
			mGlobal->setCursor( CursorType::RESIZE_RL );
            bChangedCursor = true;
		}else if(bChangedCursor){
            mGlobal->setCursor( CursorType::ARROW );
            bChangedCursor = false;
        }
		
		mouseMoved((vec2) event.getPos() - mGlobalOffset);
	}
    
	void PretzelGui::onKeyDown(ci::app::KeyEvent &event){
		//if (!bVisible) return;
		keyDown(event.getChar(), event.getCode());
	}
    
	// ---------------------------------------------------------
	void PretzelGui::draw()
    {
		if (!bVisible) return;

		auto sba = gl::ScopedBlendAlpha();
        auto sgp = gl::ScopedGlslProg( gl::getStockShader(ci::gl::ShaderDef().color() ) );
        auto sd  = gl::ScopedDepth( false );
        
      
        // -----------------------------------------------------------
        gl::color(Color(1, 1, 1));
        
        if (bDrawMinimized){
            gl::pushMatrices(); {
                gl::translate(mGlobalOffset);
                mDefaultLabel->draw();
                
                gl::color(mGlobal->P_GUI_BORDER);
                gl::drawStrokedRect(mDefaultLabel->getBounds());
            }gl::popMatrices();
        }
        else{
            gl::pushMatrices(); {
                gl::translate(mGlobalOffset);
                ScrollPane::draw();
                
                gl::color(mGlobal->P_TAB_COLOR);
                gl::drawSolidRect(Rectf(mBounds.getLowerLeft() - vec2(0, 10), mBounds.getLowerRight()));
                
                gl::color(mGlobal->P_BG_COLOR);
                gl::drawSolidTriangle(mResizeRect.getLowerLeft(), mResizeRect.getUpperRight(), mResizeRect.getLowerRight());
                
                gl::color(mGlobal->P_GUI_BORDER);
                gl::drawLine( mResizeRect.getUpperRight() - vec2(mBounds.getWidth(), 0), mResizeRect.getUpperRight() );
                gl::drawStrokedRect( Rectf(mBounds.x1, mBounds.y1, mBounds.x2, mBounds.y2) );
            }gl::popMatrices();
        }
	}
    
	// --------------------------------------------------
	void PretzelGui::addLabel(std::string labelText){
        mWidgetList.push_back( new PretzelLabel(this, labelText) );
	}
    
	void PretzelGui::addSlider(std::string label, float *variable, float min, float max){
        mWidgetList.push_back( new PretzelSlider(this, label, variable, min, max) );
	}
    
	void PretzelGui::addSlider(std::string label, int *variable, int min, int max){
		mWidgetList.push_back( new PretzelSlider(this, label, variable, min, max) );
	}
    
    void PretzelGui::addSlider(std::string label, ci::vec2 *variable, ci::vec2 min, ci::vec2 max){
		mWidgetList.push_back( new PretzelSlider(this, label, variable, min, max) );
	}
    
    void PretzelGui::addSlider(std::string label, ci::vec3 *variable, ci::vec3 min, ci::vec3 max){
		mWidgetList.push_back( new PretzelSlider(this, label, variable, min, max) );
	}
    
	void PretzelGui::addSaveLoad() {
		mWidgetList.push_back( new PretzelSaveLoad(this) );
	}
    
	void PretzelGui::addToggle(std::string label, bool *value){
		mWidgetList.push_back( new PretzelToggle(this, label, value) );
	}
    
	void PretzelGui::addTextField(std::string label, std::string *variable, bool editable){
		mWidgetList.push_back( new PretzelTextField(this, label, variable, editable) );
	}
    
    void PretzelGui::addColorPicker(std::string label, ci::Color *color){
        mWidgetList.push_back( new PretzelColorPicker(this, label, color) );
    }
    
    void PretzelGui::addColorPicker(std::string label, ci::ColorA *color){
        mWidgetList.push_back( new PretzelColorPicker(this, label, color) );
    }
}