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
        
#if defined( CINDER_MSW )
        mInstance->mCursorArrow = ::LoadCursor(NULL, IDC_ARROW);
        mInstance->mCursorIBeam = ::LoadCursor(NULL, IDC_IBEAM);
        mInstance->mCursorHand = ::LoadCursor(NULL, IDC_HAND);
        mInstance->mCursorResize = ::LoadCursor(NULL, IDC_SIZENWSE);
#endif 
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
    
    for( auto it = mGuiList.begin(); it!=mGuiList.end(); ++it){
        pg = *it;
        
        if( pg->getGlobalBounds().contains( event.getPos() ) ){
            pg->mouseDown( event.getPos() );
            break;
        }
    }
    
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
    for( auto it=mGuiList.begin(); it!=mGuiList.end(); ++it){
        (*it)->mouseDragged( event.getPos() );
    }
}
void PretzelRoot::onMouseUp(ci::app::MouseEvent &event)
{
    for( auto it=mGuiList.begin(); it!=mGuiList.end(); ++it){
        (*it)->mouseUp( event.getPos() );
    }
}
void PretzelRoot::onMouseWheel(ci::app::MouseEvent &event)
{
    for( auto it=mGuiList.begin(); it!=mGuiList.end(); ++it){
        (*it)->mouseWheel( event.getWheelIncrement() );
    }
}
void PretzelRoot::onMouseMoved(ci::app::MouseEvent &event)
{
    for( auto it=mGuiList.begin(); it!=mGuiList.end(); ++it){
        (*it)->mouseMoved( event.getPos() );
    }
}
void PretzelRoot::onKeyDown(ci::app::KeyEvent &event)
{
    for( auto it=mGuiList.begin(); it!=mGuiList.end(); ++it){
        (*it)->keyDown( event.getChar(), event.getCode() );
    }
}


