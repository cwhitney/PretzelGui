#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "pretzel/PretzelGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MultiWindowSampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
    
    pretzel::PretzelGuiRef  mGuiL, mGuiR;
    ci::Color mColLeft, mColRight;
};

void MultiWindowSampleApp::setup()
{
    mGuiL = pretzel::PretzelGui::create("Left side", 300, 300);
    mGuiL->addColorPicker("Right side color", &mColLeft);
    
    app::WindowRef newWindow = createWindow( Window::Format().size( 500, 500 ).pos(ivec2(550, 0)) );
    
    mGuiR = pretzel::PretzelGui::create("Right side", 300, 300, newWindow);
    mGuiR->addColorPicker("Left side color", &mColRight);
    
    mColLeft  = Color::hex( 0x00FFE5 );
    mColRight = Color::hex( 0xFF8A72 );
    
    ci::app::getWindowIndex(0)->setUserData( &mColRight );
    ci::app::getWindowIndex(1)->setUserData( &mColLeft );
}

void MultiWindowSampleApp::mouseDown( MouseEvent event )
{
}

void MultiWindowSampleApp::keyDown( KeyEvent event )
{
}

void MultiWindowSampleApp::update()
{
}

void MultiWindowSampleApp::draw()
{
    ci::app::WindowRef win = ci::app::getWindow();
    ci::Color *col = win->getUserData<ci::Color>();
    
	gl::clear( *col );
    
    pretzel::PretzelGui::drawAll();
}

CINDER_APP( MultiWindowSampleApp, RendererGl, [&](ci::app::App::Settings *settings){
    settings->setWindowSize(500, 500);
    settings->setWindowPos(0, 0);
})
