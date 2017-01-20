#include "components/WindowSystem.h"

#include "components/PretzelRoot.h"
#include "pretzel/PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace pretzel;

WindowSystem* WindowSystem::mInstance = NULL;

WindowSystem * WindowSystem::getInstance(){
    if (!mInstance){
        mInstance = new WindowSystem();
        mInstance->setup();
    }
    return mInstance;
}

void WindowSystem::setup()
{
    mStrokedRectVerts = gl::VertBatch(GL_LINE_STRIP);
    mStrokedRectVerts.vertex(0,0);
    mStrokedRectVerts.vertex(1,0);
    mStrokedRectVerts.vertex(1,1);
    mStrokedRectVerts.vertex(0,1);
    mStrokedRectVerts.vertex(0,0);
    
    mLineVerts = gl::VertBatch(GL_LINE_STRIP);
    mLineVerts.vertex(0,0);
    mLineVerts.vertex(1,0);
}

PWindowData* WindowSystem::getWindowData( ci::app::WindowRef window )
{
//    PWindowData *data = window->getUserData<PWindowData>();
    PWindowData *data = mDataMap[window];

    if( data == nullptr ){
        auto winData = new PWindowData();
            winData->mRoot = new PretzelRoot();
            winData->mRoot->init(window);

        // Batches can't be shared across contexts, so each window needs it's own.
        winData->mSolidRectBatch    = gl::Batch::create( geom::Rect( Rectf(0,0,1,1) ), gl::getStockShader( gl::ShaderDef().color() ) );
        winData->mStrokedRectBatch  = gl::Batch::create( mStrokedRectVerts, gl::getStockShader( gl::ShaderDef().color() ) );
        winData->mLineBatch         = gl::Batch::create( mLineVerts, gl::getStockShader( gl::ShaderDef().color() ) );

//        window->setUserData( winData );
        mDataMap[window] = winData;

        // When the window is closed, disconnect events and remove it from the master map
//        window->getSignalClose().connect(
//            [window, this](){
//            console() << "Window closed" << endl;
            //window->setUserData(nullptr);
//        });
    }

    return mDataMap[window];
//    return window->getUserData<PWindowData>();
}

void WindowSystem::drawSolidRect( ci::Rectf rect )
{
    gl::pushMatrices();
    gl::translate( rect.x1, rect.y1 );
    gl::scale( rect.getWidth(), rect.getHeight() );
    getWindowData( getWindow() )->mSolidRectBatch->draw();
    gl::popMatrices();
}

void WindowSystem::drawStrokedRect( ci::Rectf rect )
{
    gl::pushMatrices();
    gl::translate( rect.x1, rect.y1 );
    gl::scale( rect.getWidth(), rect.getHeight() );
    
    getWindowData( getWindow() )->mStrokedRectBatch->draw();
    gl::popMatrices();
}

void WindowSystem::drawLine( ci::vec2 start, ci::vec2 end )
{
    gl::pushMatrices();
    gl::translate(start);
    gl::rotate( atan2( end.y-start.y, end.x-start.x ) );
    gl::scale( vec2( glm::length(end - start) ) );
    getWindowData( getWindow() )->mLineBatch->draw();
    gl::popMatrices();
}

