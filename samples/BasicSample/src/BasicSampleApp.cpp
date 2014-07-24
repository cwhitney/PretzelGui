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
    
    Vec2f       mPosition;
    Vec3f       mVec3;
    
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
	mPosition = getWindowCenter();
	bDrawOutline = false;
	mCol = Color::white();
	mBubble = "Hello, world!";

	gui = new Pretzel::PretzelGui("Circle settings");

    // Sliders can take ints, float, Vec2, and Vec3
	gui->addSlider("Position", &mPosition, Vec2f(0,0), getWindowSize());
    
	gui->addLabel("Other Settings");
	gui->addButton("Random Color", &BasicSampleApp::onButtonPress, this);
	gui->addToggle("Draw outline", &bDrawOutline);
    gui->addColorPicker("Circle Color", &mCol);
    
    // Passing floats will keep your sliders as floats
	gui->addSlider("Opacity", &mOpacity, 0.0, 1.0);
	gui->addSlider("Radius", &mRadius, 0, 100);

	// Textfields can be editable or non-editable
	gui->addTextField("FPS", &mFps, false);
	gui->addTextField("Speech Bubble", &mBubble, true);

	gui->addSaveLoad();
    
    gui->loadSettings();    // load the last saved settings automatically
    
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
		gl::drawStrokedCircle(mPosition, mRadius);
	}else {
		gl::drawSolidCircle(mPosition, mRadius);
	}
	gl::drawString("< " + mBubble, mPosition + Vec2f(mRadius + 10, -10), mCol, Font("Arial", 24));
    
    gui->draw();
}

void BasicSampleApp::keyDown(KeyEvent event) {
	if (event.getChar() == 'g'){
		gui->toggleVisible();	// gui interaction will be disabled when invisible
	}
}

CINDER_APP_NATIVE(BasicSampleApp, RendererGl)
