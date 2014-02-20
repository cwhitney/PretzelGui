#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "PanelGui.h"
#include "PanelRow.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicSampleApp : public AppNative {
  public:
	void setup();
	void update();
	void draw();
    
    PanelGui    *gui;
    PanelRow    *titleBar, *mainBar;
};

void BasicSampleApp::setup() {
    Rand::randomize();
    
    gui = new PanelGui( PanelFillStyle::FILL, PanelFillStyle::FILL );
    titleBar = new PanelRow( gui, PanelFillStyle::FILL, 50 );
    mainBar = new PanelRow( gui, 200, PanelFillStyle::FILL );
}

void BasicSampleApp::update() {
    gui->update();
}

void BasicSampleApp::draw() {
	gl::clear( Color( 0, 0, 0 ) );
    
    gui->draw();
}

CINDER_APP_NATIVE( BasicSampleApp, RendererGl )
