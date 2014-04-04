#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "PanelGui.h"
#include "PanelRow.h"
#include "PanelLabel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicSampleApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void update();
	void draw();
    
    PanelGui    *gui;
    PanelRow    *titleBar, *mainBar;

	float		mRadius;
	float		mOpacity;
	bool		bDrawOutline;

	void onButtonPress();
};

void BasicSampleApp::prepareSettings( Settings *settings ) {
    settings->setWindowSize( Vec2i(1024, 768) );
	settings->setFrameRate(60.0);
	settings->enableConsoleWindow();
}

void BasicSampleApp::setup() {
	Rand::randomize();
    
	mRadius = 25;
	mOpacity = 1.0;
	bDrawOutline = false;

    //gui = new PanelGui( PanelFillStyle::FILL, PanelFillStyle::FILL );
	gui = new PanelGui();
    gui->setup();
	gui->addSlider("Opacity", &mOpacity, 0, 1);
	gui->addSlider("Radius", &mRadius, 0, 100);
	gui->addLabel("Other Settings");
	gui->addSaveLoad();
	gui->addButton("Resize", &BasicSampleApp::onButtonPress, this);
	gui->addToggle("Draw outline", &bDrawOutline);

	//titleBar = new PanelRow(gui, PanelFillStyle::FILL, PanelFillStyle::FILL);
    //mainBar = new PanelRow( gui, 200, PanelFillStyle::FILL );
}
void BasicSampleApp::onButtonPress(){
	console() << "Got a button press event" << endl;
	gui->setSize( Vec2f(200, 400) );

}


void BasicSampleApp::update() {

}

void BasicSampleApp::draw() {
	gl::clear( Color( 84./255.,166./255., 1 ) );
    gl::color( ColorA(1,1,1, mOpacity) );
    
	if (bDrawOutline){
		gl::drawStrokedCircle(getWindowCenter(), mRadius);
	}
	else{
		gl::drawSolidCircle(getWindowCenter(), mRadius);
	}
	//console() << "VALUE " << testSliderValue << endl;

    gui->draw();
}

CINDER_APP_NATIVE( BasicSampleApp, RendererGl )
