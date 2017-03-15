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

namespace pretzel
{
    // STATIC ---------------
    PretzelGuiRef PretzelGui::create(std::string title){
        return create(title, 200, 500);
    }
    
    PretzelGuiRef PretzelGui::create(std::string title, int width, int height, ci::app::WindowRef window) {
        return std::make_shared<PretzelGui>(title, width, height, window);
    }
    
    void PretzelGui::drawAll()
    {
        PWindow()->getWindowData(ci::app::getWindow())->mRoot->draw();
        
//        for( auto gui : guiList ){
//            gui->draw();
//        }
		
		gl::color(Color::white());
    }
    
    // NORMAL -----------------
	PretzelGui::PretzelGui(std::string title, int width, int height, ci::app::WindowRef window) :
        ScrollPane(nullptr, width, height),
        mWindowRef(window)
    {
        init(title);
    }

    PretzelGui::~PretzelGui()
    {
        //  Remove all modules, disconnect signals
        while( mWidgetList.size() )
        {
            BasePretzel *w = mWidgetList.back();
            
            if( w->type == WidgetType::BUTTON ){
                ((PretzelButton*)w)->mConnection.disconnect();
            }
            mWidgetList.pop_back();
            delete w;
        }
        
        delete mDefaultLabel;
    }
    
    // Initialize the gui with a title
	void PretzelGui::init(std::string title)
    {
        mGlobal->P_ACTIVE_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 340)));
		mGlobal->P_HOVER_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 360)));
		mGlobal->P_GUI_BORDER = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 380)));
		mGlobal->P_BG_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 400)));
		mGlobal->P_TAB_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 420)));
		mGlobal->P_TEXT_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 440)));
		mGlobal->P_OUTLINE_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 460)));
		mGlobal->P_HIGHLIGHT_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 480)));
		mGlobal->P_SLIDER_COLOR = ColorA(mGlobal->mSkinSurf.getPixel(ci::vec2(10, 500)));
        
        mGlobal->signalOnSettingsLoad.connect( std::bind(&PretzelGui::onSettingsLoaded, this) );
        
		mGlobalOffset = vec2(10, 10);
//        mGlobal->setGlobalPos( mGlobalOffset );
        
		vec2 ul = mBounds.getSize() - vec2(10, 10);
		vec2 lr = mBounds.getSize();
		mResizeRect.set(ul.x, ul.y, lr.x, lr.y);
        
		mGlobal->renderText("");	// initialize the font
        
		if (title == ""){
			title = "Settings";
		}
		mDefaultLabel = new PretzelLabel(this, title);
        
//        auto pretzelRoot = pretzel()->getWindowData(mWindowRef)->mRoot;
//        PretzelRoot* pretzelRoot = static_cast<PretzelRoot*>( pretzel()->getWindowData(mWindowRef)->mRoot );
//        PWindowData *winData;       // TEMP TMP
//        winData->mGuiList.push_back(this);
        
        PWindow()->getWindowData(mWindowRef)->mRoot->addChild(this);
        
//        PretzelRoot::getInstance()->addChild(this);
	}
    
    ci::Rectf PretzelGui::getBounds(){
        if( bDrawMinimized ){
            return mDefaultLabel->getBounds();
        }
        
        return ScrollPane::getBounds();
    }
    
    ci::Rectf PretzelGui::getGlobalBounds()
    {
        if( bDrawMinimized ){
            Rectf b = mDefaultLabel->getBounds();
            b.offset( mGlobalOffset );
            return b;
        }
        
        return ScrollPane::getGlobalBounds();
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
//        mGlobal->setGlobalPos( pos );
	}
    
    // Programatically minimize the gui. Same as double-clicking the top bar
	void PretzelGui::minimize(bool doMinimize){
		bDrawMinimized = doMinimize;
	}
    
    // Renders the gui visible/invisible and connects/disconnects all listener signals
	void PretzelGui::setVisible(bool visible){
		console() << mDefaultLabel->getText() << " Set visible :: " << visible << endl;
		bVisible = visible;
	}
    
    // Toggles the gui visible/invisible and connects/disconnects all listener signals
	void PretzelGui::toggleVisible(){
		bVisible = !bVisible;
	}
    
	bool PretzelGui::isVisible(){
		return bVisible;
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
	void PretzelGui::mouseDown(const ci::vec2 &pos){
		if (!bVisible) return;
        
		if (mDefaultLabel->getBounds().contains(pos - mGlobalOffset)){
            
			if (getElapsedSeconds() - mLastClickTime < 0.25){               // Double click title bar, minimize
				bDrawMinimized = !bDrawMinimized;
			}
			else{                                                           // Single click title bar, drag
				bDragging = true;
				mMouseOffset = pos - mGlobalOffset;
			}
			mLastClickTime = getElapsedSeconds();
		}
		else if (bDrawMinimized){                                           // We are minimized, don't go further
			return;
		}
		else if (mResizeRect.contains(pos - mGlobalOffset)){                // Hit in lower right corner for resize
			bResizing = true;
			mResizeStartSize = mBounds.getSize();
			mMouseOffset = pos - mGlobalOffset;
		}
		else{
			ScrollPane::mouseDown(pos - mGlobalOffset);                      // Propagate to children
		}
	}
    
	void PretzelGui::mouseDragged(const ci::vec2 &pos){
		if (!bVisible) return;
        
		if (bDragging){
			mGlobalOffset = pos - mMouseOffset;
		}
		else if (bResizing){
			vec2 newSize = mResizeStartSize + pos - mGlobalOffset - mMouseOffset;
			setSize(newSize);
		}
		else{
			ScrollPane::mouseDragged(pos - mGlobalOffset);
		}
	}
    
	void PretzelGui::mouseUp(const ci::vec2 &pos){
		if (!bVisible) return;
        
		if (bDragging){
			bDragging = false;
		}
		else if (bResizing){
			bResizing = false;
		}
		else{
			ScrollPane::mouseUp(pos - mGlobalOffset);
		}
	}
    
	void PretzelGui::mouseMoved(const ci::vec2 &pos){
		if (!bVisible) return;
        
        ScrollPane::mouseMoved(pos - mGlobalOffset);
        
        if (mDefaultLabel->getBounds().contains(pos - mGlobalOffset)){
            mGlobal->setCursor( CursorType::HAND );
            bChangedCursor = true;
        }else if (mResizeRect.contains(pos - mGlobalOffset)){	// Hit in lower right corner for resize
			mGlobal->setCursor( CursorType::RESIZE_RL );
            bChangedCursor = true;
		}else if(bChangedCursor){
            mGlobal->setCursor( CursorType::ARROW );
            bChangedCursor = false;
        }
	}
    
    void PretzelGui::mouseWheel(const float increment) {
        ScrollPane::mouseWheel( increment * 4.0 );
    }
    
	void PretzelGui::keyDown(const char &key, const int &keyCode){
		//if (!bVisible) return;
		ScrollPane::keyDown(key, keyCode);
	}
    
	// ---------------------------------------------------------
	void PretzelGui::draw()
    {
		if (!bVisible) return;

        ScrollPane::draw();
        
		gl::ScopedBlendAlpha();
        gl::ScopedGlslProg sgp( gl::getStockShader(ci::gl::ShaderDef().color()) );
        gl::ScopedDepth sd( false );
      
        // -----------------------------------------------------------
        gl::color(Color(1, 1, 1));
        
        if (bDrawMinimized){
            gl::pushMatrices(); {
                gl::translate(mGlobalOffset);
                mDefaultLabel->draw();
                
                gl::color(mGlobal->P_GUI_BORDER);
                PWindow()->drawStrokedRect(mDefaultLabel->getBounds());
            }gl::popMatrices();
        }
        else{
            gl::pushMatrices(); {
                gl::translate(mGlobalOffset);
                ScrollPane::draw();
                
                gl::color(mGlobal->P_TAB_COLOR);
                PWindow()->drawSolidRect(Rectf(mBounds.getLowerLeft() - vec2(0, 10), mBounds.getLowerRight()));
                
                gl::color(mGlobal->P_BG_COLOR);
                gl::drawSolidTriangle(mResizeRect.getLowerLeft(), mResizeRect.getUpperRight(), mResizeRect.getLowerRight());
                
                gl::color(mGlobal->P_GUI_BORDER);
                PWindow()->drawLine( mResizeRect.getUpperRight() - vec2(mBounds.getWidth(), 0), mResizeRect.getUpperRight() );
                PWindow()->drawStrokedRect( Rectf(mBounds.x1, mBounds.y1, mBounds.x2, mBounds.y2) );
            }gl::popMatrices();
        }
	}
    
	// --------------------------------------------------
	PretzelLabel* PretzelGui::addLabel(std::string labelText){
        mWidgetList.push_back( new PretzelLabel(this, labelText) );
        return (PretzelLabel*)mWidgetList.back();
	}
    
	PretzelSlider* PretzelGui::addSlider(std::string label, float *variable, float min, float max){
        mWidgetList.push_back( new PretzelSlider(this, label, variable, min, max) );
        return (PretzelSlider*)mWidgetList.back();
	}
    
	PretzelSlider* PretzelGui::addSlider(std::string label, int *variable, int min, int max){
		mWidgetList.push_back( new PretzelSlider(this, label, variable, min, max) );
        return (PretzelSlider*)mWidgetList.back();
	}
    
    PretzelSlider* PretzelGui::addSlider(std::string label, ci::vec2 *variable, ci::vec2 min, ci::vec2 max){
		mWidgetList.push_back( new PretzelSlider(this, label, variable, min, max) );
        return (PretzelSlider*)mWidgetList.back();
	}
    
    PretzelSlider* PretzelGui::addSlider(std::string label, ci::vec3 *variable, ci::vec3 min, ci::vec3 max){
		mWidgetList.push_back( new PretzelSlider(this, label, variable, min, max) );
        return (PretzelSlider*)mWidgetList.back();
	}
    
	PretzelSaveLoad* PretzelGui::addSaveLoad() {
		mWidgetList.push_back( new PretzelSaveLoad(this) );
        return (PretzelSaveLoad*)mWidgetList.back();
	}
    
	PretzelToggle* PretzelGui::addToggle(std::string label, bool *value){
		mWidgetList.push_back( new PretzelToggle(this, label, value) );
        return (PretzelToggle*)mWidgetList.back();
	}
    
	PretzelTextField* PretzelGui::addTextField(std::string label, std::string *variable, bool editable){
		mWidgetList.push_back( new PretzelTextField(this, label, variable, editable) );
        return (PretzelTextField*)mWidgetList.back();
	}
    
    PretzelColorPicker* PretzelGui::addColorPicker(std::string label, ci::Color *color){
        mWidgetList.push_back( new PretzelColorPicker(this, label, color) );
        return (PretzelColorPicker*)mWidgetList.back();
    }
    
    PretzelColorPicker* PretzelGui::addColorPicker(std::string label, ci::ColorA *color){
        mWidgetList.push_back( new PretzelColorPicker(this, label, color) );
        return (PretzelColorPicker*)mWidgetList.back();
    }
    
    PretzelEnum* PretzelGui::addEnum(std::string label, std::vector<std::string> *strList, int *num){
        mWidgetList.push_back( new PretzelEnum(this, label, strList, num) );
        return (PretzelEnum*)mWidgetList.back();
    }
}
