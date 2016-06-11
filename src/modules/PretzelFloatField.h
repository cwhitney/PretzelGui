#pragma once

#include "modules/PretzelTextField.h"

namespace pretzel{
	class PretzelFloatField : public PretzelTextField{
	 public:
		 PretzelFloatField(BasePretzel *parent, std::string labelText, float &variable, bool editable = true);
		 void keyDown(const char &key, const int &keyCode) override;
		 void setLimits(float low, float high);

	protected:
		bool isCharValid(int keyCode) const override;

	private:
		std::string mStr;
		float &mVar;
		float mLim[2];
		static std::string tempStr;
	};
}