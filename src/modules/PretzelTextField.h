#pragma once

#include "pretzel/PretzelGlobal.h"
#include "components/BasePretzel.h"
#include "cinder/app/App.h"

/* TODO:
 - make textfield clip and scroll text
 - accept int and float variables
 - allow to move cursor position with mouse or arrow keys
 - allow copypaste
 - lose focus after not editing for a while?
 - fire signals on start and end editing, like iOS
*/

namespace pretzel{
	class PretzelTextField : public BasePretzel{
	  public:
		PretzelTextField(BasePretzel *parent, std::string labelText, std::string *variable, bool editable = true);
        
	
        void draw() override;
        void updateBounds(const ci::vec2 &offset, const ci::RectT<float> &parentBounds) override;
        
        void mouseDown(const ci::vec2 &pos) override;
        void mouseMoved(const ci::vec2 &pos) override;
        void keyDown(const char &key, const int &keyCode) override;
     private:   
        std::string		mLabelText;
		std::string		*mVariable;
		ci::Rectf		mTextFieldBounds;
		ci::vec2		mLabelSize;
		ci::vec2		mInputSize;

		bool			bHover;
		bool            bEditable;
		bool            bEditing;
	};
}