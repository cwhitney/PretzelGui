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
    
    pretzel::PretzelGuiRef  mGui1, mGui2;
    
    float b0=0, b1=0, b2=0, b3=0, b4=0;
    
};

void MultiWindowSampleApp::setup()
{
    mGui1 = pretzel::PretzelGui::create("Window 1", 350, 300);
    mGui1->addSlider("slider 1", &b0, -1.0, 1.0);
    mGui1->addSlider("slider 2", &b1, -1.0, 1.0);
    mGui1->addSlider("slider 3", &b2, -1.0, 1.0);
    
    
    app::WindowRef newWindow = createWindow( Window::Format().size( 500, 500 ).pos(ivec2(550, 0)) );
    
    mGui2 = pretzel::PretzelGui::create("Window 2", 350, 300, newWindow);
    mGui2->addSlider("slider 4", &b3, -1.0, 1.0);
    mGui2->addSlider("slider 5", &b4, -1.0, 1.0);
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
	gl::clear( Color( 0, 0, 0 ) );
    
    pretzel::PretzelGui::drawAll();
//    mGui1->draw();
//    mGui2->draw();
}

CINDER_APP( MultiWindowSampleApp, RendererGl, [&](ci::app::App::Settings *settings){
    settings->setWindowSize(500, 500);
    settings->setWindowPos(0, 0);
})
