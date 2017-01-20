#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace pretzel
{
    class PretzelGui;
    class PretzelRoot;
    
    // --------------------------------------------------
    class PWindowData {
      public:
        PretzelRoot*                mRoot;
        ci::gl::BatchRef            mSolidRectBatch, mStrokedRectBatch, mLineBatch;
    };
    
    // --------------------------------------------------
    class WindowSystem {
      public:
        static WindowSystem* getInstance();
        
        PWindowData* getWindowData( ci::app::WindowRef window );
        
        void drawSolidRect( ci::Rectf rect );
        void drawStrokedRect( ci::Rectf rect );
        void drawLine( ci::vec2 start, ci::vec2 end );
        
      private:
        void setup();
        ci::gl::VertBatch   mRectVerts, mStrokedRectVerts, mLineVerts;
        
        std::map<ci::app::WindowRef, PWindowData *>   mDataMap;
        
        // PRIVATE CONSTRUCTOR + COPY
        WindowSystem(){};
        WindowSystem(WindowSystem const&){};
        static WindowSystem		*mInstance;
    };

    inline pretzel::WindowSystem*	PWindow()	{ return WindowSystem::getInstance(); }
}
