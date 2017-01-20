#include "PretzelLabel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel{
	PretzelLabel::PretzelLabel(BasePretzel *parent, std::string labelText) : BasePretzel(), scrollPaneOffset(0,0)
    {
		mMessage = labelText;
        type = WidgetType::LABEL;
		mBounds.set(0, 0, 200, 23);
        
		parent->registerPretzel(this);

		mGlobal = pretzel::PretzelGlobal::getInstance();
	}

	void PretzelLabel::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds)
    {
		BasePretzel::updateBounds(offset, parentBounds);

		vec2 textSize = mGlobal->guiFont->measureString(mMessage);
		RectT<float> textRect(0, 0, textSize.x, textSize.y);
		textRect.y2 = mBounds.getHeight();
		textRect.x1 += -5 + 15;
		textRect.x2 += 5 + 15;

		mOutlinePath.clear();
		mOutlinePath.moveTo(mBounds.getLowerLeft() + vec2(0, -1));
		mOutlinePath.lineTo(textRect.getLowerLeft() + vec2(0, -1));
		mOutlinePath.lineTo(vec2(textRect.getUpperLeft().x, 3));
		mOutlinePath.lineTo(vec2(textRect.getUpperRight().x, 3));
		mOutlinePath.lineTo(textRect.getLowerRight() + vec2(0, -1));
		mOutlinePath.lineTo(mBounds.getLowerRight() + vec2(0, -1));
	}

	void PretzelLabel::draw()
    {
		vec2 textSize = mGlobal->guiFont->measureString(mMessage);
		RectT<float> textRect(0, 0, textSize.x, textSize.y);
		textRect.y1 = 4;
		textRect.y2 = mBounds.getHeight()-1;
		textRect.x1 -= 5;
		textRect.x2 += 5;

		gl::pushMatrices(); {
			gl::translate(mOffset + scrollPaneOffset);

			// draw light background
			gl::color(mGlobal->P_TAB_COLOR);
            PWindow()->drawSolidRect(mBounds);

			gl::pushMatrices(); {
				gl::translate(15, 1);

				// draw dark background
				gl::color(mGlobal->P_BG_COLOR);
                PWindow()->drawSolidRect(textRect);

				// draw text
				mGlobal->renderText(mMessage, mBounds.getUpperLeft() + vec2(0, 4));
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
}
