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

PretzelRoot* PretzelRoot::mInstance = NULL;
PretzelRoot* PretzelRoot::getInstance(){
    if (!mInstance){
        mInstance = new PretzelRoot();
        mInstance->init();
    }
    return mInstance;
}

void PretzelRoot::init()
{
    connectSignals();
}

PretzelRoot::~PretzelRoot()
{
    disconnectSignals();
}

void PretzelRoot::connectSignals(){
    if( !mMouseBeganCallBack.isConnected() ){
        ci::app::WindowRef window = cinder::app::getWindow();
        
        // uses default priority 0
        mMouseBeganCallBack = window->getSignalMouseDown().connect(std::bind(&PretzelRoot::onMouseDown, this, std::placeholders::_1));
        mMouseDragCallBack = window->getSignalMouseDrag().connect(std::bind(&PretzelRoot::onMouseDragged, this, std::placeholders::_1));
        mMouseEndCallBack = window->getSignalMouseUp().connect(std::bind(&PretzelRoot::onMouseUp, this, std::placeholders::_1));
        mMouseMovedCallBack = window->getSignalMouseMove().connect(std::bind(&PretzelRoot::onMouseMoved, this, std::placeholders::_1));
        mKeyDownCallback = window->getSignalKeyDown().connect(std::bind(&PretzelRoot::onKeyDown, this, std::placeholders::_1));
        mMouseWheelCallBack = window->getSignalMouseWheel().connect(std::bind(&PretzelRoot::onMouseWheel, this, std::placeholders::_1));
    }
}

void PretzelRoot::disconnectSignals(){
    if( mMouseBeganCallBack.isConnected() ){
        mMouseBeganCallBack.disconnect();
        mMouseDragCallBack.disconnect();
        mMouseEndCallBack.disconnect();
        mMouseMovedCallBack.disconnect();
        mKeyDownCallback.disconnect();
        mMouseWheelCallBack.disconnect();
    }
}

void PretzelRoot::addChild( PretzelGui *gui )
{
    mGuiList.push_front( gui );
}


void PretzelRoot::draw()
{
    for( auto it = mGuiList.rbegin(); it!=mGuiList.rend(); ++it){
        (*it)->draw();
    }
}

/* TODO
    -- check for visibility
*/

void PretzelRoot::onMouseDown(ci::app::MouseEvent &event)
{
    PretzelGui *pg;
    
    // only click the top-most gui
    for( auto it = mGuiList.begin(); it!=mGuiList.end(); ++it){
        pg = *it;
        
        if( pg->getGlobalBounds().contains( event.getPos() ) ){
            pg->mouseDown( event.getPos() );
            break;
        }
    }
    
    // If this gui isn't on top, do z sorting to bring it up
    if( pg != mGuiList[0] ){
        for( auto it = mGuiList.begin(); it!=mGuiList.end(); ){
            if( *it == pg ){
                it = mGuiList.erase(it);
            }else{
                ++it;
            }
        }
        
        mGuiList.push_front(pg);
    }
}
void PretzelRoot::onMouseDragged(ci::app::MouseEvent &event)
{
    mGuiList[0]->mouseDragged( event.getPos() );
    
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
    mGuiList[0]->mouseUp( event.getPos() );
    
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
    mGuiList[0]->mouseWheel( event.getWheelIncrement() );
    
//    for( auto it = mGuiList.begin(); it!=mGuiList.end(); ++it){
//        PretzelGui *pg = *it;
//        
//        if( pg->getGlobalBounds().contains( event.getPos() ) ){
//            (*it)->mouseWheel( event.getWheelIncrement() );
//            break;
//        }
//    }
}
void PretzelRoot::onMouseMoved(ci::app::MouseEvent &event)
{
//    for( auto it=mGuiList.begin(); it!=mGuiList.end(); ++it){
//        (*it)->mouseMoved( event.getPos() );
//    }
    
    for( auto it = mGuiList.begin(); it!=mGuiList.end(); ++it){
        PretzelGui *pg = *it;
        
        if( pg->getGlobalBounds().contains( event.getPos() ) ){
            (*it)->mouseMoved( event.getPos() );
            break;
        }
    }
}
void PretzelRoot::onKeyDown(ci::app::KeyEvent &event)
{
    mGuiList[0]->keyDown( event.getChar(), event.getCode() );
    
//    for( auto it = mGuiList.begin(); it!=mGuiList.end(); ++it){
//        PretzelGui *pg = *it;
//        
//        if( pg->getGlobalBounds().contains( event.getPos() ) ){
//            (*it)->keyDown( event.getChar(), event.getCode() );
//        }
//    }
}


