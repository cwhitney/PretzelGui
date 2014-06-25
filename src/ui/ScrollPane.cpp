//
//  ScrollPane.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 6/24/14.
//
//

#include "ScrollPane.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel {

    ScrollPane::ScrollPane(BasePretzel *base, int width, int height) : PretzelRow(base, width, height) {
        
    }

    void ScrollPane::draw(){
        glEnable(GL_SCISSOR_TEST);
        Rectf tBounds = mBounds;
        Vec2f tPos = mOffset;
        float winH = getWindowHeight();

        if( ci::app::App::get()->getSettings().isHighDensityDisplayEnabled() ){
            tBounds *= getWindowContentScale();
            winH *= getWindowContentScale();
            tPos *= getWindowContentScale();
        }

        glScissor( tPos.x, winH - tBounds.y2 - tPos.y, tBounds.getWidth(), tBounds.getHeight());
        
        gl::translate(mOffset);
        PretzelRow::draw();
        
//        gl::color(mGlobal->P_TAB_COLOR);
//        gl::drawSolidRect(Rectf(mBounds.getLowerLeft() - Vec2i(0, 10), mBounds.getLowerRight()));
//        
//        gl::color(mGlobal->P_BG_COLOR);
//        gl::drawSolidTriangle(mResizeRect.getLowerLeft(), mResizeRect.getUpperRight(), mResizeRect.getLowerRight());
//        
//        gl::color(mGlobal->P_GUI_BORDER);
//        gl::drawLine( mResizeRect.getUpperRight() - Vec2f(mBounds.getWidth(), 0), mResizeRect.getUpperRight() );
//        gl::drawStrokedRect( Rectf(mBounds.x1, mBounds.y1, mBounds.x2, mBounds.y2) );
        
        glDisable(GL_SCISSOR_TEST);
    }
}