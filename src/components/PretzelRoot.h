//
//  PretzelRoot.h
//  MultiGuiSample
//
//  Created by Charlie Whitney on 11/6/15.
//
//

#pragma once

#include "cinder/app/App.h"

#include "pretzel/PretzelGlobal.h"
#include "pretzel/PretzelGui.h"

namespace pretzel
{
    class PretzelGui;
    
    // ------------------------------------------------
    class PWindowData {
      public:
        PWindowData() {};
        std::deque<PretzelGui*>    mGuiList;
    };
    
    // ------------------------------------------------
    class PretzelRoot
    {
      public:
//        static PretzelRoot* getInstance();
        static PretzelRoot* getRootForWindow( ci::app::WindowRef window );
        
        void addChild( PretzelGui *gui );
        void update();
        void draw();
        
      protected:
        
      private:
        PretzelRoot() {};
        PretzelRoot(PretzelRoot const&){};
        ~PretzelRoot();
        
        static PretzelRoot                                  *mInstance;
        static  std::map<ci::app::WindowRef, PretzelRoot*>  mRootsMap;
        
//        void init();
        void init( ci::app::WindowRef win );
        
        // EVENTS ---------------------------
        void connectSignals(ci::app::WindowRef window);
        void disconnectSignals();
        
        void onMouseDown(   ci::app::MouseEvent &event  );
        void onMouseDragged(ci::app::MouseEvent &event  );
        void onMouseUp(     ci::app::MouseEvent &event  );
        void onMouseWheel(  ci::app::MouseEvent &event  );
        void onMouseMoved(  ci::app::MouseEvent &event  );
        void onKeyDown(     ci::app::KeyEvent &event    );
        
        // mouse events
        ci::signals::Connection mMouseBeganCallback,
                                mMouseDragCallback,
                                mMouseEndCallback,
                                mMouseWheelCallback,
                                mMouseMovedCallback,
                                mKeyDownCallback,
                                mUpdateCallback;
        
        // ----------
//        std::deque<PretzelGui*>    mGuiList;
    };
}
