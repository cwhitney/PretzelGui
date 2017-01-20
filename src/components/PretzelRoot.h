//
//  PretzelRoot.h
//  MultiGuiSample
//
//  Created by Charlie Whitney on 11/6/15.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/Batch.h"

#include "pretzel/PretzelGui.h"
#include "pretzel/PretzelGlobal.h"

namespace pretzel
{    
    // ------------------------------------------------
    using PretzelRootRef = std::shared_ptr<class PretzelRoot>;
    
    class PretzelRoot
    {
      public:
        PretzelRoot() {};
        ~PretzelRoot();
        
        void init( ci::app::WindowRef win );
        
        void addChild( PretzelGui *gui );
        void update();
        
        void draw();
        
      protected:
        
      private:
       
        
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
        std::deque<PretzelGui*>    mGuiList;
    };
}
