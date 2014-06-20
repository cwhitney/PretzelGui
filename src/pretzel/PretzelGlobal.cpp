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
			emHeight = floor( guiFont->measureString("M").y );
		}
#ifdef TARGET_OS_MAC
        pos -= Vec2i(0, 2);
#endif

		ci::gl::TextureFont::DrawOptions opts;
		opts.pixelSnap(true);

		ci::Vec2f textSize = guiFont->measureString(text);

		ci::gl::pushMatrices(); {
			ci::gl::color(P_TEXT_COLOR);

			if (align == FontAlignment::ALIGN_RIGHT){
				guiFont->drawString(text, ci::Vec2i(-textSize.x, 0) + pos + Vec2i(0,emHeight), opts);
			}
			else if (align == FontAlignment::ALIGN_CENTER){
				guiFont->drawString(text, ci::Vec2i((int)textSize.x*-0.5, 0) + pos + Vec2i(0,emHeight), opts);
			}
			else{
				guiFont->drawString(text, pos + Vec2i(0,emHeight), opts);
			}
		}ci::gl::popMatrices();
	}

	void PretzelGlobal::renderText(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, FontAlignment::ALIGN_LEFT);
	}

	void PretzelGlobal::renderTextRight(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, FontAlignment::ALIGN_RIGHT);
	}

	void PretzelGlobal::renderTextCentered(std::string text, ci::Vec2i pos) {
		renderTextInternal(text, pos, FontAlignment::ALIGN_CENTER);
	}
    
    void PretzelGlobal::setCursor( CursorType type ){
        
#if defined( CINDER_MAC )
        switch(type){
            case CursorType::ARROW :
                [[NSCursor arrowCursor] set];
                break;
            case CursorType::IBEAM :
                [[NSCursor IBeamCursor] set];
                break;
            case CursorType::HAND :
                [[NSCursor pointingHandCursor] set];
                break;
            case CursorType::RESIZE_RL :
                [[NSCursor resizeLeftRightCursor] set];
                break;
            default:
                break;
        }
//        + (NSCursor *)operationNotAllowedCursor NS_AVAILABLE_MAC(10_5);
//        + (NSCursor *)dragLinkCursor NS_AVAILABLE_MAC(10_6);
//        + (NSCursor *)dragCopyCursor NS_AVAILABLE_MAC(10_6);
//        + (NSCursor *)contextualMenuCursor NS_AVAILABLE_MAC(10_6);
//        + (NSCursor *)IBeamCursorForVerticalLayout NS_AVAILABLE_MAC(10_7);
#endif
    }


	// SAVING ----------------------------------------------
	void PretzelGlobal::addSaveParam(std::string name, float *val){
		addParamInternal(name, val, _FLOAT);
	}

	void PretzelGlobal::addSaveParam(std::string name, int *val){
		addParamInternal(name, val, _INT);
	}

	void PretzelGlobal::addSaveParam(std::string name, bool *val){
		addParamInternal(name, val, _BOOL);
	}

	void PretzelGlobal::addSaveParam(std::string name, std::string *val){
		addParamInternal(name, val, _STRING);
	}

	void PretzelGlobal::addParamInternal(std::string name, void* value, PretzelTypes type){
		PretzelParam p;
		p.name = name;
		p.value = value;
		p.type = type;

		mParamList.push_back(p);
	}

	void PretzelGlobal::saveSettings(fs::path settingsPath){
		fs::path appPath = settingsPath;

		if (appPath.string() == ""){
#ifdef _WIN32
			appPath = getAppPath() / "guiSettings";
#else
			appPath = getAppPath().parent_path() / "guiSettings";
#endif
			if (!fs::exists(appPath)){
				console() << appPath << " does not exist" << endl;
				fs::create_directory(appPath);
			}
			appPath /= "settings.json";
		}

		JsonTree pSettings = JsonTree::makeObject("pretzelSettings");
		std::string tmp;
		for (int i = 0; i < mParamList.size(); i++){
			switch (mParamList[i].type){
			case _FLOAT:
				pSettings.pushBack(JsonTree(mParamList[i].name, to_string(*(float*)mParamList[i].value)));
				break;
			case _INT:
				pSettings.pushBack(JsonTree(mParamList[i].name, to_string(*(int*)mParamList[i].value)));
				break;
			case _BOOL:
				tmp = ((*(bool*)mParamList[i].value) == true) ? "1" : "0";
				pSettings.pushBack(JsonTree(mParamList[i].name, tmp));
				break;
			case _STRING:
				pSettings.pushBack(JsonTree(mParamList[i].name, (*(std::string*)mParamList[i].value)));
				break;
			default:
				break;
			}
		}

		JsonTree root;
		root.pushBack(pSettings);
		root.write(appPath, JsonTree::WriteOptions());
	}

	void PretzelGlobal::loadSettings(fs::path settingsPath){
		fs::path loadPath = settingsPath;
		if (loadPath.string() == ""){
			
#ifdef _WIN32
			loadPath = getAppPath() / "guiSettings" / "settings.json";
#else
            loadPath = getAppPath().parent_path() / "guiSettings" / "settings.json";
#endif
		}

		if (!fs::exists(loadPath)){
			console() << loadPath << " does not exist" << endl;
		}
		else{
			JsonTree loadTree(loadFile(loadPath));
			JsonTree appSettings = loadTree.getChild(0);

			for (int i = 0; i < mParamList.size(); i++){
				string pName = mParamList[i].name;
				switch (mParamList[i].type){
				case _FLOAT:
					if (appSettings.hasChild(pName)){
						float fVal = appSettings.getChild(pName).getValue<float>();
						*((float*)mParamList[i].value) = fVal;
					}
					break;
				case _INT:
					if (appSettings.hasChild(pName)){
						int fVal = appSettings.getChild(pName).getValue<int>();
						*((int*)mParamList[i].value) = fVal;
					}
					break;
				case _BOOL:
					if (appSettings.hasChild(pName)){
						bool bVal = appSettings.getChild(pName).getValue<float>();
						*((bool*)mParamList[i].value) = bVal;
					}
					break;
				case _STRING:
					if (appSettings.hasChild(pName)){
						std::string sVal = appSettings.getChild(pName).getValue<std::string>();
						*((std::string*)mParamList[i].value) = sVal;
					}
					break;
				default:
					console() << "Pretzel :: Can't load settings type " << endl;
					break;
				}
			}
		}
	}


}
