#include "PanelLabel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

PanelLabel::PanelLabel(BasePanel *parent, std::string labelText) : BasePanel(){
	mMessage = labelText;
	//boost::to_upper(mMessage);

	mBounds.set(0, 0, 200, 23);
	parent->registerPanel(this);

	mGlobal = Panel::PanelGlobal::getInstance();
}

void PanelLabel::registerPanel(BasePanel *panel){
	console() << "You can't add a child to a label" << endl;
}

void PanelLabel::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
	BasePanel::updateBounds(offset, parentBounds);

	Vec2f textSize = mGlobal->guiFont->measureString(mMessage);
	Rectf textRect(0, 0, textSize.x, textSize.y);
	textRect.y2 = mBounds.getHeight();
	textRect.x1 += -5 + 15;
	textRect.x2 += 5 + 15;

	mOutlinePath.clear();
	mOutlinePath.moveTo(mBounds.getLowerLeft() + Vec2f(0,-1));
	mOutlinePath.lineTo(textRect.getLowerLeft() + Vec2f(0, -1));
	mOutlinePath.lineTo( Vec2f(textRect.getUpperLeft().x, 3 ));
	mOutlinePath.lineTo( Vec2f(textRect.getUpperRight().x, 3));
	mOutlinePath.lineTo(textRect.getLowerRight() + Vec2f(0, -1));
	mOutlinePath.lineTo(mBounds.getLowerRight() + Vec2f(0, -1));
}

void PanelLabel::draw(){
	Vec2f textSize = mGlobal->guiFont->measureString(mMessage);
	Rectf textRect(0, 0, textSize.x, textSize.y);
	textRect.y1 = 4;
	textRect.y2 = mBounds.getHeight();
	textRect.x1 -= 5;
	textRect.x2 += 5;

	gl::pushMatrices(); {
		gl::translate(mOffset);

		gl::color(mGlobal->P_OUTLINE_COLOR);
		gl::drawLine(mBounds.getLowerLeft(), mBounds.getLowerRight());

		// draw light background
		gl::color(mGlobal->P_TAB_COLOR);
		gl::drawSolidRect(mBounds);

		gl::pushMatrices(); {
			gl::translate(15, 1);
		
			// draw dark background
			gl::color(mGlobal->P_BG_COLOR);
			gl::drawSolidRect(textRect);

			// draw text
			mGlobal->renderText(mMessage, mBounds.getUpperLeft() + Vec2f(0, 4));
		}gl::popMatrices();

		// draw highlight line
		gl::translate(0, 1);
		gl::color(mGlobal->P_HIGHLIGHT_COLOR);
		gl::draw(mOutlinePath);

		gl::translate(0, -1);
		gl::color(mGlobal->P_OUTLINE_COLOR);
		gl::draw(mOutlinePath);

		
	}gl::popMatrices();
}