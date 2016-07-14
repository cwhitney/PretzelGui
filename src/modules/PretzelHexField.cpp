#include "PretzelHexField.h"

using namespace ci;
using namespace ci::app;
using namespace std;

pretzel::PretzelHexField::PretzelHexField(BasePretzel *parent, string labelText, unsigned &variable, bool editable)
    : PretzelTextField(parent, labelText, &tempStr, editable )
	, mVar(variable) {
	mLim[0] = numeric_limits<unsigned>::min();
	mLim[1] = numeric_limits<unsigned>::max();
	mVar = clamp(mVar, mLim[0], mLim[1]);

	// curses!  to_string does not support radix other than 10
	// mStr = to_string(variable); 
	mStr = hex_to_string(mVar);
	mVariable = &mStr;
}

std::string pretzel::PretzelHexField::hex_to_string(unsigned u)
{
	char buf[32];
#ifdef CINDER_MSW
	_ultoa(u, buf, 16);
#elif CINDER_OSX
    ultoa(u, buf, 16);
#endif
    
    
    console() << "buff :: " << buf << endl;
    
	return string(buf);
}

void pretzel::PretzelHexField::keyDown(const char &key, const int &keyCode) {
	PretzelTextField::keyDown(key, keyCode);
	mVar = mStr.empty() ? 0 : stoul(mStr, 0, 16);

	unsigned test = clamp(mVar, mLim[0], mLim[1]);

	if (test != mVar)
	{
		mVar = test;
		mStr = hex_to_string(mVar);
	}
}

void pretzel::PretzelHexField::setLimits(unsigned low, unsigned high)
{
	mLim[0] = low;
	mLim[1] = high;
}

bool pretzel::PretzelHexField::isCharValid(int keyCode) const {
	return (keyCode >= KeyEvent::KEY_0  && keyCode <= KeyEvent::KEY_9) 
		|| (keyCode >= KeyEvent::KEY_KP0 && keyCode <= KeyEvent::KEY_KP9)
		|| (keyCode >= 'A'   && keyCode <= 'F')
		|| (keyCode >= KeyEvent::KEY_a   && keyCode <= KeyEvent::KEY_f);
}

std::string pretzel::PretzelHexField::tempStr;