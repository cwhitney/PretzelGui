#pragma once

#include "PretzelGlobal.h"
#include "BasePretzel.h"
#include "cinder/app/AppNative.h"

/* TODO:
 - make textfield clip and scroll text
 - accept int and float variables
 - lose focus after not editing for a while?
 - allow copypaste
 - fire signals on start and end editing, like iOS
*/

namespace Pretzel{
	class PretzelTextField : public BasePretzel{
	public:
		PretzelTextField(BasePretzel *parent, std::string labelText, std::string *variable, bool editable = true);

		virtual void draw();
		void updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds);

		virtual void mouseDown(const ci::Vec2i &pos);
		virtual void mouseMoved(const ci::Vec2i &pos);
        virtual void keyDown(const char &key, const int &keyCode);
        
	private:
        std::string		mLabelText;
		std::string		*mVariable;
		ci::Rectf		mTextFieldBounds;
		ci::Vec2f		mLabelSize;
		ci::Vec2f		mInputSize;

		bool			bHover;
		bool            bEditable;
		bool            bEditing;
	};
}