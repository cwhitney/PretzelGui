#include "PretzelTextField.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel{
	PretzelTextField::PretzelTextField(BasePretzel *parent, std::string labelText, std::string *variable, bool editable) : BasePretzel() {
		mBounds.set(0, 0, 200, 26);
		
		bEditable = editable;
		bHover = false;
		bEditing = false;
		mLabelText = labelText;
        mVariable = variable;
		mLabelSize = mGlobal->guiFont->measureString(mLabelText);
		mInputSize = mGlobal->guiFont->measureString(*variable);
		
		if(bEditable) mGlobal->addSaveParam(labelText, variable);
		parent->registerPretzel(this);
	}

	void PretzelTextField::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds) {
		BasePretzel::updateBounds(offset, parentBounds);

		// this could be cleaner
		mTextFieldBounds = Rectf(mLabelSize.x + 25, mBounds.y1 + 5, mBounds.x2 - 10, mBounds.y2 - 5);
	}

	void PretzelTextField::mouseDown(const ci::Vec2i &pos){
		if (bEditable && mTextFieldBounds.contains(pos - mOffset)){
            bEditing = true;
		}
        else{
            bEditing = false;
        }
	}

	void PretzelTextField::mouseMoved(const ci::Vec2i &pos){
		if (bEditable && mTextFieldBounds.contains(pos - mOffset)){
			bHover = true;
		}
		else{
			bHover = false;
		}
	}
    
    // Mayus and character combinations not working yet
    void PretzelTextField::keyDown(const char &key, const int &keyCode){
        if (bEditing){
            if (keyCode == KeyEvent::KEY_ESCAPE || keyCode == KeyEvent::KEY_RETURN){
                bEditing = false;
            }
            else if (keyCode == KeyEvent::KEY_BACKSPACE){
                mVariable->pop_back();
            }
            else if (keyCode > 31 && keyCode < 127){ //printable characters
                mVariable->push_back(key);
            }
			mInputSize = mGlobal->guiFont->measureString(*mVariable);
        }
    }

	void PretzelTextField::draw(){
		gl::pushMatrices(); {
			gl::translate(mOffset);
            
            if(bEditing){
				gl::color(mGlobal->P_HOVER_COLOR);
			}
			else if (bHover){
				gl::color(mGlobal->P_TAB_COLOR);
			}
			else{
				gl::color(mGlobal->P_BG_COLOR);
			}
			gl::drawSolidRect(mTextFieldBounds);

			gl::color(mGlobal->P_HIGHLIGHT_COLOR);
			gl::drawLine(mTextFieldBounds.getLowerLeft() + Vec2f(0, 1), mTextFieldBounds.getLowerRight() + Vec2f(0, 1));
            
            gl::color(mGlobal->P_OUTLINE_COLOR);
			gl::drawStrokedRect(mTextFieldBounds);

            mGlobal->renderText(mLabelText, mBounds.getUpperLeft() + Vec2i(12, 5));
            mGlobal->renderText(*mVariable, mTextFieldBounds.getUpperLeft() + Vec2i(2, 0));
			
			// cursor line
			if (bEditing && (app::getElapsedSeconds() - (long)app::getElapsedSeconds()) < 0.5 ){
				float x = mTextFieldBounds.getUpperLeft().x + mInputSize.x + 6;
				gl::color(mGlobal->P_TEXT_COLOR);
				gl::drawLine(Vec2i(x, mTextFieldBounds.y1 + 2), Vec2i(x, mTextFieldBounds.y2 - 3));
			}
		}gl::popMatrices();
	}
}