//
//  PretzelRoot.cpp
//  MultiGuiSample
//
//  Created by Charlie Whitney on 11/6/15.
//
//

#include "PretzelRoot.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace pretzel;

//PretzelRoot* PretzelRoot::mInstance = NULL;
std::map<ci::app::WindowRef, PretzelRoot*> PretzelRoot::mRootsMap;

/*
PretzelRoot* PretzelRoot::getInstance(){
    if (!mInstance){
        mInstance = new PretzelRoot();
        mInstance->init();
    }
    return mInstance;
}*/

PretzelRoot* PretzelRoot::getRootForWindow( ci::app::WindowRef window )
{
    if( mRootsMap.count(window) == 0 ){
        auto pr = new PretzelRoot();
        pr->init(window);
        mRootsMap[window] = pr;
    }
    
    return mRootsMap[window];
}

//void PretzelRoot::init()
//{
//    init( getWindow() );
//}

void PretzelRoot::init( ci::app::WindowRef win )
{
    PWindowData *data = win->getUserData<PWindowData>();
    if( data == nullptr ){
        win->setUserData( new PWindowData() );
    }
    
    connectSignals( win );
    
    // When the window is closed, disconnect events and remove it from the master map
    win->getSignalClose().connect(
        [win, this](){
            console() << "Window closed" << endl;
            this->disconnectSignals();
            mRootsMap.erase(win);
        }
    );
}

PretzelRoot::~PretzelRoot()
{
    disconnectSignals();
}

void PretzelRoot::connectSignals(ci::app::WindowRef window)
{
    if( !mMouseBeganCallback.isConnected() ){
        //ci::app::WindowRef window = cinder::app::getWindow();
        
        // uses default priority 0
        mMouseBeganCallback = window->getSignalMouseDown().connect(std::bind(&PretzelRoot::onMouseDown, this, std::placeholders::_1));
        mMouseDragCallback = window->getSignalMouseDrag().connect(std::bind(&PretzelRoot::onMouseDragged, this, std::placeholders::_1));
        mMouseEndCallback = window->getSignalMouseUp().connect(std::bind(&PretzelRoot::onMouseUp, this, std::placeholders::_1));
        mMouseMovedCallback = window->getSignalMouseMove().connect(std::bind(&PretzelRoot::onMouseMoved, this, std::placeholders::_1));
        mKeyDownCallback = window->getSignalKeyDown().connect(std::bind(&PretzelRoot::onKeyDown, this, std::placeholders::_1));
        mMouseWheelCallback = window->getSignalMouseWheel().connect(std::bind(&PretzelRoot::onMouseWheel, this, std::placeholders::_1));
        
        mUpdateCallback = ci::app::App::get()->getSignalUpdate().connect(std::bind(&PretzelRoot::update, this));
    }
}

void PretzelRoot::disconnectSignals()
{
    if( mMouseBeganCallback.isConnected() ){
        mMouseBeganCallback.disconnect();
        mMouseDragCallback.disconnect();
        mMouseEndCallback.disconnect();
        mMouseMovedCallback.disconnect();
        mKeyDownCallback.disconnect();
        mMouseWheelCallback.disconnect();
        mUpdateCallback.disconnect();
    }
}

void PretzelRoot::addChild( PretzelGui *gui )
{
    PWindowData *data = getWindow()->getUserData<PWindowData>();
    if( data == nullptr){
        CI_LOG_E("Couldn't add module. Window not initialized.");
        return;
    }
    data->mGuiList.push_front( gui );
}

void PretzelRoot::update()
{
    auto win = getWindow();
    if( win == nullptr){
        return;
    }
    
    PWindowData *data = win->getUserData<PWindowData>();
    if( data == nullptr){
        return;
    }
    auto guiList = data->mGuiList;
    
    for( auto it = guiList.rbegin(); it!=guiList.rend(); ++it){
        (*it)->update();
    }
}

void PretzelRoot::draw()
{
    // TODO, loop through all windows checking for guis    
    
    PWindowData *data = getWindow()->getUserData<PWindowData>();
    if( data == nullptr){
        return;
    }
    
    // Draw all submodules
    auto guiList = data->mGuiList;
    for( auto it = guiList.rbegin(); it!=guiList.rend(); ++it){
        (*it)->draw();
    }
}

/* TODO
    -- check for visibility
*/

void PretzelRoot::onMouseDown(ci::app::MouseEvent &event)
{
    PretzelGui *pg;
    PWindowData *data = getWindow()->getUserData<PWindowData>();
    auto guiList = data->mGuiList;
    
    // only click the top-most gui
    for( auto it = guiList.begin(); it!=guiList.end(); ++it){
        pg = *it;
        
        if( pg->getGlobalBounds().contains( event.getPos() ) ){
            pg->mouseDown( event.getPos() );
            break;
        }
    }
    
    // If this gui isn't on top, do z sorting to bring it up
    if( pg != guiList[0] ){
        for( auto it = guiList.begin(); it!=guiList.end(); ){
            if( *it == pg ){
                it = guiList.erase(it);
            }else{
                ++it;
            }
        }
        
        guiList.push_front(pg);
    }
}
void PretzelRoot::onMouseDragged(ci::app::MouseEvent &event)
{
    PWindowData *data = getWindow()->getUserData<PWindowData>();
    data->mGuiList[0]->mouseDragged( event.getPos() );
    
//    for( auto it = mGuiList.begin(); it!=mGuiList.end(); ++it){
//        PretzelGui *pg = *it;
//        
//        if( pg->getGlobalBounds().contains( event.getPos() ) ){
//            (*it)->mouseDragged( event.getPos() );
//            break;
//        }
//    }
}
void PretzelRoot::onMouseUp(ci::app::MouseEvent &event)
{
    PWindowData *data = getWindow()->getUserData<PWindowData>();
    data->mGuiList[0]->mouseUp( event.getPos() );
    
//    for( auto it = mGuiList.begin(); it!=mGuiList.end(); ++it){
//        PretzelGui *pg = *it;
//        
//        if( pg->getGlobalBounds().contains( event.getPos() ) ){
//            (*it)->mouseUp( event.getPos() );
//            break;
//        }
//    }
}
void PretzelRoot::onMouseWheel(ci::app::MouseEvent &event)
{
    // TODO: this should only happen on the front gui.  Make sure to hit test it though.
    
    //    mGuiList[0]->mouseWheel( event.getWheelIncrement() );
    
    PWindowData *data = getWindow()->getUserData<PWindowData>();
    auto guiList = data->mGuiList;
    
    for( auto it = guiList.begin(); it!=guiList.end(); ++it){
        PretzelGui *pg = *it;
        
        if( pg->getGlobalBounds().contains( event.getPos() ) ){
            (*it)->mouseWheel( event.getWheelIncrement() );
            break;
        }
    }
}
void PretzelRoot::onMouseMoved(ci::app::MouseEvent &event)
{
//    for( auto it=mGuiList.begin(); it!=mGuiList.end(); ++it){
//        (*it)->mouseMoved( event.getPos() );
//    }
    PWindowData *data = getWindow()->getUserData<PWindowData>();
    auto guiList = data->mGuiList;
    
    for( auto it = guiList.begin(); it!=guiList.end(); ++it){
        PretzelGui *pg = *it;
        
        if( pg->getGlobalBounds().contains( event.getPos() ) ){
            (*it)->mouseMoved( event.getPos() );
            break;
        }
    }
}
void PretzelRoot::onKeyDown(ci::app::KeyEvent &event)
{
    PWindowData *data = getWindow()->getUserData<PWindowData>();
    
    data->mGuiList[0]->keyDown( event.getChar(), event.getCode() );
    
//    for( auto it = mGuiList.begin(); it!=mGuiList.end(); ++it){
//        PretzelGui *pg = *it;
//        
//        if( pg->getGlobalBounds().contains( event.getPos() ) ){
//            (*it)->keyDown( event.getChar(), event.getCode() );
//        }
//    }
}


