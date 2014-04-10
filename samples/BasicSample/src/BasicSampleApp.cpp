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

	PretzelGui    *gui;

	float		mRadius;
	float		mOpacity;
	bool		bDrawOutline;

	void onButtonPress();
};

void BasicSampleApp::prepareSettings(Settings *settings) {
	settings->setWindowSize(Vec2i(1024, 768));
	settings->setFrameRate(60.0);
}

void BasicSampleApp::setup() {
	Rand::randomize();

	mRadius = 25;
	mOpacity = 0.5;
	bDrawOutline = false;

	gui = new PretzelGui("My settings");
	gui->addSlider("Opacity", &mOpacity, 0.0, 1.0);
	gui->addSlider("Radius", &mRadius, 0, 100);

	gui->addLabel("Other Settings");
	gui->addSaveLoad();
	gui->addButton("Resize", &BasicSampleApp::onButtonPress, this);
	gui->addToggle("Draw outline", &bDrawOutline);

//	gui->minimize();

	ci::gl::enableAlphaBlending();
}
void BasicSampleApp::onButtonPress(){
	console() << "Got a button press event" << endl;
	gui->setSize(Vec2f(200, 400));
}


void BasicSampleApp::update() {

}

void BasicSampleApp::draw() {
	gl::clear(Color(84. / 255., 166. / 255., 1));
	gl::color(ColorA(1.0, 1.0, 1.0, mOpacity));

	if (bDrawOutline){
		gl::drawStrokedCircle(getWindowCenter(), mRadius);
	}
	else{
		gl::drawSolidCircle(getWindowCenter(), mRadius);
	}

	gui->draw();
}

CINDER_APP_NATIVE(BasicSampleApp, RendererGl)
