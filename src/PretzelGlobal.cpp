//
//  PretzelGlobal.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/21/14.
//
//

#include "PretzelGlobal.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel {
	PretzelGlobal* PretzelGlobal::mInstance = NULL;
	enum {
		Pretzel_FONT_ALIGN_LEFT,
		Pretzel_FONT_ALIGN_RIGHT,
		Pretzel_FONT_ALIGN_CENTER
	};

	PretzelGlobal * PretzelGlobal::getInstance(){
		if (!mInstance){
			mInstance = new PretzelGlobal();
		}
		return mInstance;
	}

	void PretzelGlobal::renderTextInternal(std::string text, ci::Vec2i pos, int align){
		if (!guiFont){
#ifdef _WIN32
			ci::Font tmp("Arial", 16);
#else
			ci::Font tmp("Arial", 12);
#endif
			guiFont = ci::gl::TextureFont::create(tmp);
			emHeight = guiFont->measureString("M").y;
		}

		ci::gl::TextureFont::DrawOptions opts;
		opts.pixelSnap(true);

		ci::Vec2f textSize = guiFont->measureString(text);

		ci::gl::pushMatrices(); {
			ci::gl::translate(pos);
			ci::gl::translate(0, (int)emHeight);

			ci::gl::color(P_TEXT_COLOR);

			if (align == Pretzel_FONT_ALIGN_RIGHT){
				guiFont->drawString(text, ci::Vec2i(-textSize.x, 0), opts);
			}
			else if (align == Pretzel_FONT_ALIGN_CENTER){
				guiFont->drawString(text, ci::Vec2i((int)textSize.x*-0.5, 0), opts);
			}
			else{
				guiFont->drawString(text, ci::Vec2i::zero(), opts);
			}
		}ci::gl::popMatrices();
	}

	void PretzelGlobal::renderText(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, Pretzel_FONT_ALIGN_LEFT);
	}

	void PretzelGlobal::renderTextRight(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, Pretzel_FONT_ALIGN_RIGHT);
	}

	void PretzelGlobal::renderTextCentered(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, Pretzel_FONT_ALIGN_CENTER);
	}

	// SAVING ----------------------------------------------
	void PretzelGlobal::addSaveParam(std::string name, float *val){
		addParamInternal(name, val, _FLOAT);
	}

	void PretzelGlobal::addSaveParam(std::string name, bool *val){
		addParamInternal(name, val, _BOOL);
	}

	void PretzelGlobal::addParamInternal(std::string name, void* value, PretzelTypes type){
		PretzelParam p;
		p.name = name;
		p.value = value;
		p.type = type;

		mParamList.push_back( p );
	}

	void PretzelGlobal::saveSettings(fs::path &settingsPath){
		fs::path appPath = settingsPath;

		if (appPath.string() == ""){
			appPath = getAppPath() / "guiSettings";
			if (!fs::exists(appPath)){
				console() << appPath << " does not exist" << endl;
				fs::create_directory(appPath);
			}
			appPath /= "settings.json";
		}

		JsonTree pSettings = JsonTree::makeObject( "pretzelSettings" );
		std::string tmp;
		for (int i = 0; i < mParamList.size(); i++){
			switch (mParamList[i].type){
			case _FLOAT:
				pSettings.pushBack( JsonTree(mParamList[i].name, to_string(*(float*)mParamList[i].value)) );
				break;
			case _BOOL:
				tmp = ((*(bool*)mParamList[i].value) == true) ? "1" : "0";
				pSettings.pushBack(JsonTree(mParamList[i].name, tmp));
				break;
			default:
				break;
			}
		}

		JsonTree root;
		root.pushBack(pSettings);
		root.write(appPath, JsonTree::WriteOptions());
	}

	void PretzelGlobal::loadSettings(fs::path &settingsPath){
		fs::path loadPath = settingsPath;
		if (loadPath.string() == ""){
			loadPath = getAppPath() / "guiSettings" / "settings.json";
		}

		if (!fs::exists(loadPath)){
			console() << loadPath << " does not exist" << endl;
		}
		else{
			JsonTree loadTree(loadFile(loadPath));
			console() << "LOAD TREE " << loadTree << endl;
		}
	}


}
