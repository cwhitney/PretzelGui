#include "PretzelFloatField.h"
#include <limits>
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

pretzel::PretzelFloatField::PretzelFloatField(BasePretzel *parent, string labelText, float &variable, bool editable)
    : PretzelTextField(parent, labelText, &tempStr, editable )
	, mVar(variable) {
	mLim[0] = numeric_limits<float>::lowest();
	mLim[1] = numeric_limits<float>::max();
	mVar = clamp(mVar, mLim[0], mLim[1]);
	mStr = to_string(mVar);
	mVariable = &mStr;
}

void pretzel::PretzelFloatField::keyDown(const char &key, const int &keyCode) {
	PretzelTextField::keyDown(key, keyCode);
	if (mStr.empty())
		mVar = 0;
	else if (mStr.size() == 1 && (mStr[0] == '-' || mStr[0] == '+' || mStr[0] == '.'))
		mVar = 0;
	else
		mVar = stof(mStr);

	float test = clamp(mVar, mLim[0], mLim[1]);

	if (test != mVar)
	{
		mVar = test;
		mStr = to_string(mVar);
	}
}

void pretzel::PretzelFloatField::setLimits(float low, float high)
{
	mLim[0] = low;
	mLim[1] = high;
}

bool pretzel::PretzelFloatField::isCharValid(int keyCode) const {
	bool valid = (keyCode >= KeyEvent::KEY_0  && keyCode <= KeyEvent::KEY_9) 
		|| (keyCode >= KeyEvent::KEY_KP0 && keyCode <= KeyEvent::KEY_KP9) 
		|| (keyCode == KeyEvent::KEY_PERIOD || keyCode == KeyEvent::KEY_KP_PERIOD);

	if (!valid && mStr.empty())
		valid = keyCode == KeyEvent::KEY_PLUS || keyCode == KeyEvent::KEY_MINUS
		|| keyCode == KeyEvent::KEY_KP_PLUS || keyCode == KeyEvent::KEY_KP_MINUS;

	return valid;
}


std::string pretzel::PretzelFloatField::tempStr;
