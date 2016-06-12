#pragma once

#include "modules/PretzelTextField.h"

namespace pretzel{
	class PretzelIntField : public PretzelTextField{
	 public:
		 PretzelIntField(BasePretzel *parent, std::string labelText, int &variable, bool editable = true);
		 void keyDown(const char &key, const int &keyCode) override;
		 void setLimits(int low, int high);

	protected:
		bool isCharValid(int keyCode) const override;

		void draw() override
		{
			mStr = std::to_string(mVar);
			PretzelTextField::draw();
		}


	private:
		std::string mStr;
		int &mVar;
		int mLim[2];

		static std::string tempStr;
	};
}