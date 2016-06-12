#pragma once

#include "modules/PretzelTextField.h"

namespace pretzel{
	class PretzelDoubleField : public PretzelTextField {
	 public:
		 PretzelDoubleField(BasePretzel *parent, std::string labelText, double &variable, bool editable = true);
		 void keyDown(const char &key, const int &keyCode) override;
		 void setLimits(double low, double high);

	protected:
		bool isCharValid(int keyCode) const override;

		void draw() override
		{
			mStr = std::to_string(mVar);
			PretzelTextField::draw();
		}

	private:
		std::string mStr;
		double &mVar;
		double mLim[2];
		static std::string tempStr;
	};
}