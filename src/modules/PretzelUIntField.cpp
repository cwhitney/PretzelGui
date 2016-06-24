#include "PretzelUIntField.h"
#include <limits>
#include "cinder\CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

pretzel::PretzelUIntField::PretzelUIntField(BasePretzel *parent, string labelText, unsigned &variable, bool editable)
    : PretzelTextField(parent, labelText, &tempStr, editable )
	, mVar(variable) {
	mLim[0] = numeric_limits<unsigned>::min();
	mLim[1] = numeric_limits<unsigned>::max();
	mVar = clamp(mVar, mLim[0], mLim[1]);
	mStr = to_string(mVar);
	mVariable = &mStr;
}

void pretzel::PretzelUIntField::keyDown(const char &key, const int &keyCode) {
	PretzelTextField::keyDown(key, keyCode);
	mVar = mStr.empty() ? 0 : stoul(mStr);

	unsigned test = clamp(mVar, mLim[0], mLim[1]);

	if (test != mVar)
	{
		mVar = test;
		mStr = to_string(mVar);
	}
}

void pretzel::PretzelUIntField::setLimits(unsigned low, unsigned high)
{
	mLim[0] = low;
	mLim[1] = high;
}

bool pretzel::PretzelUIntField::isCharValid(int keyCode) const {
	return (keyCode >= KeyEvent::KEY_0  && keyCode <= KeyEvent::KEY_9) || (keyCode >= KeyEvent::KEY_KP0 && keyCode <= KeyEvent::KEY_KP9);
}


std::string pretzel::PretzelUIntField::tempStr;