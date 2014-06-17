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

	Pretzel::PretzelGui    *gui;

	float		mRadius;
	float		mOpacity;
	int			xShift;
	bool		bDrawOutline;

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
	mOpacity = 0.5;
	xShift = 0;
	bDrawOutline = false;
	mCol = Color::white();

	gui = new Pretzel::PretzelGui("Circle settings");

	// Passing floats will keep your sliders as floats
	gui->addSlider("Opacity", &mOpacity, 0.0, 1.0);
	gui->addSlider("Radius", &mRadius, 0, 100);

	// Int sliders have the same signature
	gui->addSlider("X Shift", &xShift, -100, 100);

	gui->addLabel("Other Settings");
	gui->addButton("Random Color", &BasicSampleApp::onButtonPress, this);
	gui->addToggle("Draw outline", &bDrawOutline);
	gui->addSaveLoad();

//	gui->minimize();

	ci::gl::enableAlphaBlending();
}
void BasicSampleApp::onButtonPress(){
	//gui->setSize(Vec2f(200, 400));
	mCol = ColorA(Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), mOpacity);
}


void BasicSampleApp::update() {

}

void BasicSampleApp::draw() {
	gl::clear(Color(84. / 255., 166. / 255., 1));

	mCol.a = mOpacity;

	gl::color(mCol);

	if (bDrawOutline){
		gl::drawStrokedCircle(getWindowCenter() + Vec2f(xShift,0), mRadius);
	}
	else{
		gl::drawSolidCircle(getWindowCenter() + Vec2f(xShift, 0), mRadius);
	}

	gui->draw();
}

CINDER_APP_NATIVE(BasicSampleApp, RendererGl)
