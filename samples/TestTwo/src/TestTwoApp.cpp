#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "PanelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TestTwoApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    PanelGui    *gui;
    
    float testOne;
};

void TestTwoApp::setup()
{
    testOne = 50.0;
    
    gui = new PanelGui();
    gui->setup();
    gui->addSlider( "radius", &testOne, 0.0, 100.0);
}

void TestTwoApp::mouseDown( MouseEvent event )
{
}

void TestTwoApp::update()
{
}

void TestTwoApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::drawSolidCircle( getWindowCenter(), testOne);
    
    gui->draw();
}

CINDER_APP_NATIVE( TestTwoApp, RendererGl )
