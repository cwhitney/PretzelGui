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
    
    class PretzelRoot
    {
      public:
        static PretzelRoot* getInstance();
        
        void addChild( PretzelGui *gui );
        void update();
        void draw();
        
      protected:
        
      private:
        PretzelRoot() {};
        PretzelRoot(PretzelRoot const&){};
        ~PretzelRoot();
        static PretzelRoot		*mInstance;
        
        void init();
        
        // EVENTS ---------------------------
        void connectSignals();
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
        std::deque<PretzelGui*>    mGuiList;
    };
}