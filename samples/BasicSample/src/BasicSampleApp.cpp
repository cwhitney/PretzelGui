#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasicSampleApp : public AppNative {
public:
	void prepareSettings(Settings *settings);
	void setup();
	void update();
	void draw();
	void keyDown(KeyEvent event);

	Pretzel::PretzelGui    *gui;

	float		mRadius;
	float		mOpacity;
	int			xShift;
	bool		bDrawOutline;
	std::string mFps;
	std::string mBubble;

	ci::ColorA	mCol;

	void onButtonPress();
};

void BasicSampleApp::prepareSettings(Settings *settings) {
	settings->setWindowSize(Vec2i(1024, 768));
	settings->setFrameRate(60.0);
    settings->enableHighDensityDisplay();
}

void BasicSampleApp::setup() {
	Rand::randomize();

	mRadius = 25;
	mOpacity = 0.75;
	xShift = 0;
	bDrawOutline = false;
	mCol = Color::white();
	mBubble = "Hello, world!";

	gui = new Pretzel::PretzelGui("Circle settings");
	
	// Passing floats will keep your sliders as floats
	gui->addSlider("Opacity", &mOpacity, 0.0, 1.0);
	gui->addSlider("Radius", &mRadius, 0, 100);

	// Int sliders have the same signature
	gui->addSlider("X Shift", &xShift, -100, 100);

	gui->addLabel("Other Settings");
	gui->addButton("Random Color", &BasicSampleApp::onButtonPress, this);
	gui->addToggle("Draw outline", &bDrawOutline);

	// Textfields can be editable or non-editable
	gui->addTextField("FPS", &mFps, false);
	gui->addTextField("Speech Bubble", &mBubble, true);

	gui->addSaveLoad();
    
//  gui->loadSettings();    // load the last saved settings automatically
    
//	gui->minimize();        // start in a minimized mode (same as double-clicking the top bar)

	ci::gl::enableAlphaBlending();
}
void BasicSampleApp::onButtonPress(){
	mCol = ColorA(Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), mOpacity);
}

void BasicSampleApp::update() {
	mFps = toString((int)getAverageFps());
}

void BasicSampleApp::draw() {
	gl::clear(Color(84. / 255., 166. / 255., 1));

	mCol.a = mOpacity;

	gl::color(mCol);

	if (bDrawOutline){
		gl::drawStrokedCircle(getWindowCenter() + Vec2f(xShift,0), mRadius);
	}else {
		gl::drawSolidCircle(getWindowCenter() + Vec2f(xShift, 0), mRadius);
	}
	gl::drawString("< " + mBubble, getWindowCenter() + Vec2f(xShift + mRadius + 10, -10), mCol, Font("Arial", 24));
    
    gui->draw();
}

void BasicSampleApp::keyDown(KeyEvent event) {
	if (event.getChar() == 'g'){
		gui->toggleVisible();	// gui interaction will be disabled when invisible
	}
}

CINDER_APP_NATIVE(BasicSampleApp, RendererGl)
