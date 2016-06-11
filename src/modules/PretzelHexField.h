#pragma once

#include "modules/PretzelTextField.h"

namespace pretzel{
	class PretzelHexField : public PretzelTextField{
	 public:
		 PretzelHexField(BasePretzel *parent, std::string labelText, unsigned &variable, bool editable = true);
		 void keyDown(const char &key, const int &keyCode) override;
		 void setLimits(unsigned low, unsigned high);
		 static std::string hex_to_string(unsigned u);

	protected:
		bool isCharValid(int keyCode) const override;

	private:
		std::string mStr;
		unsigned &mVar;
		unsigned mLim[2];

		static std::string tempStr;
	};
}