#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "pretzel/PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MultiGuiSampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    pretzel::PretzelGuiRef  mGuiL, mGuiR;
    ci::Color mColLeft, mColRight;
};

void MultiGuiSampleApp::setup()
{
    mGuiL = pretzel::PretzelGui::create("Left side", 300, 400);
    mGuiL->addColorPicker("Left side color", &mColLeft);
    mGuiL->addSaveLoad();
    
    mGuiR = pretzel::PretzelGui::create("Right side", 300, 400);
    mGuiR->setPos( vec2(200, 10) );
    mGuiR->addColorPicker("Right side color", &mColRight);
    mGuiR->addSaveLoad();
    
    mGuiL->loadSettings();
}

void MultiGuiSampleApp::mouseDown( MouseEvent event )
{
}

void MultiGuiSampleApp::update()
{
}

void MultiGuiSampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color( mColLeft );
    gl::drawSolidRect( Rectf(0,0,getWindowWidth()*0.5, getWindowHeight()) );
    
    gl::color( mColRight );
    gl::drawSolidRect( Rectf(getWindowWidth()*0.5,0,getWindowWidth(), getWindowHeight()) );
    
    pretzel::PretzelGui::drawAll();
}

CINDER_APP( MultiGuiSampleApp, RendererGl, [&]( App::Settings *settings){
    settings->setWindowSize(1024, 768);
})
