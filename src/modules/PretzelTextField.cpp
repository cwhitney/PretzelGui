#include "PretzelTextField.h"
#include "cinder/app/App.h"
#include "cinder/app/Window.h"
#include "cinder/Utilities.h"
//#include "NSCursor.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel{
	PretzelTextField::PretzelTextField(BasePretzel *parent, std::string labelText, std::string *variable, bool editable) : BasePretzel() {
		mBounds.set(0, 0, 200, 26);
		
		bEditable = editable;
		bHover = false;
		bEditing = false;
		mLabelText = labelText;
        mVariable = variable;
		mLabelSize = mGlobal->guiFont->measureString(mLabelText);
		mInputSize = mGlobal->guiFont->measureString(*variable);
        type = WidgetType::TEXTFIELD;
		
		if(bEditable) mGlobal->addSaveParam(labelText, variable);
		parent->registerPretzel(this);
	}

	void PretzelTextField::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) {
		BasePretzel::updateBounds(offset, parentBounds);

		// this could be cleaner
		mTextFieldBounds = Rectf(mLabelSize.x + 25, mBounds.y1 + 5, mBounds.x2 - 10, mBounds.y2 - 5);
	}

	void PretzelTextField::mouseDown(const ci::vec2 &pos){
		if (bEditable && mTextFieldBounds.contains(pos - mOffset)){
            bEditing = true;
		}
        else{
            bEditing = false;
        }
	}

	void PretzelTextField::mouseMoved(const ci::vec2 &pos){
		if (bEditable && mTextFieldBounds.contains(pos - mOffset)){
			bHover = true;
            mGlobal->setCursor( CursorType::IBEAM );
		}
		else{
            if( bHover ){
                mGlobal->setCursor( CursorType::ARROW );
            }
			bHover = false;
		}
	}
    
    // Mayus and character combinations not working yet
    void PretzelTextField::keyDown(const char &key, const int &keyCode){
        if (bEditing){
            if (keyCode == KeyEvent::KEY_ESCAPE || keyCode == KeyEvent::KEY_RETURN){
                bEditing = false;
            }
            else if (keyCode == KeyEvent::KEY_BACKSPACE && !mVariable->empty()){
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
			PWindow()->drawSolidRect(mTextFieldBounds);

			gl::color(mGlobal->P_HIGHLIGHT_COLOR);
			PWindow()->drawLine(mTextFieldBounds.getLowerLeft() + vec2(0, 1), mTextFieldBounds.getLowerRight() + vec2(0, 1));
            
            gl::color(mGlobal->P_OUTLINE_COLOR);
            PWindow()->drawStrokedRect(mTextFieldBounds);

            mGlobal->renderText(mLabelText, mBounds.getUpperLeft() + vec2(12, 5));
            mGlobal->renderText(*mVariable, mTextFieldBounds.getUpperLeft() + vec2(2, 0));
			
			// cursor line
			if (bEditing && (app::getElapsedSeconds() - (long)app::getElapsedSeconds()) < 0.5 ){
				float x = mTextFieldBounds.getUpperLeft().x + mInputSize.x + 4;
				gl::color(mGlobal->P_TEXT_COLOR);
				PWindow()->drawLine(vec2(x, mTextFieldBounds.y1 + 2), vec2(x, mTextFieldBounds.y2 - 2));
			}
		}gl::popMatrices();
	}
}
