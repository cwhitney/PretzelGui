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

#if defined( CINDER_MAC )
#import <AppKit/AppKit.h>
#endif

namespace pretzel {
	PretzelGlobal* PretzelGlobal::mInstance = NULL;

    PretzelGlobal * PretzelGlobal::getInstance(){
		if (!mInstance){
			mInstance = new PretzelGlobal();
            mInstance->setup();

#if defined( CINDER_MSW )
		mInstance->mCursorArrow     = ::LoadCursor(NULL, IDC_ARROW);
		mInstance->mCursorIBeam     = ::LoadCursor(NULL, IDC_IBEAM);
		mInstance->mCursorHand      = ::LoadCursor(NULL, IDC_HAND);
		mInstance->mCursorResize    = ::LoadCursor(NULL, IDC_SIZENWSE);
#endif 
		}
		return mInstance;
	}
    /*
    PWindowData* PretzelGlobal::getWindowData( ci::app::WindowRef window )
    {
        PWindowData *data = window->getUserData<PWindowData>();
        
        if( data == nullptr ){
            auto winData = new PWindowData();
//            winData->mRoot = new PretzelRoot(); //std::make_shared<PretzelRoot>();
//            winData->mRoot->init(window);     // TODO get init back in
            
            // Batches can't be shared across contexts, so each window needs it's own.
            winData->mSolidRectBatch    = gl::Batch::create( geom::Rect( Rectf(0,0,1,1) ), gl::getStockShader( gl::ShaderDef().color() ) );
            winData->mStrokedRectBatch  = gl::Batch::create( mStrokedRectVerts, gl::getStockShader( gl::ShaderDef().color() ) );
            winData->mLineBatch         = gl::Batch::create( mLineVerts, gl::getStockShader( gl::ShaderDef().color() ) );
            
            window->setUserData( winData );
            
            // When the window is closed, disconnect events and remove it from the master map
            window->getSignalClose().connect(
                [window, this](){
                    console() << "Window closed" << endl;
                    //window->setUserData(nullptr);
                });
        }
        
        return window->getUserData<PWindowData>();
    }*/
    
    void PretzelGlobal::setup()
    {
        mSkinSurf = Surface(loadImage(ci::app::loadResource( PRETZEL_GUI_SKIN )));
        mSkinTex = gl::Texture::create(mInstance->mSkinSurf);
        
//        //mSolidRectBatch = gl::Batch::create( geom::Rect( Rectf(0,0,1,1) ), gl::getStockShader( gl::ShaderDef().color() ) );
//        
//        mStrokedRectVerts = gl::VertBatch(GL_LINE_STRIP);
//        mStrokedRectVerts.vertex(0,0);
//        mStrokedRectVerts.vertex(1,0);
//        mStrokedRectVerts.vertex(1,1);
//        mStrokedRectVerts.vertex(0,1);
//        mStrokedRectVerts.vertex(0,0);
//        //mStrokedRectBatch = gl::Batch::create( vb, gl::getStockShader( gl::ShaderDef().color() ) );
//        
//        mLineVerts = gl::VertBatch(GL_LINE_STRIP);
//        mLineVerts.vertex(0,0);
//        mLineVerts.vertex(1,0);
        //mLineBatch = gl::Batch::create( vl, gl::getStockShader( gl::ShaderDef().color() ) );
    }

	void PretzelGlobal::renderTextInternal(std::string text, ci::vec2 pos, int align){
		if (!guiFont){
#if defined( CINDER_MSW )
			ci::Font tmp("Arial", 16);
#else
			ci::Font tmp("Arial", 12);
#endif
			guiFont = ci::gl::TextureFont::create(tmp);
			emHeight = floor( guiFont->measureString("M").y );
		}
#if defined( CINDER_MAC )
        pos -= vec2(0, 2);
#endif

		ci::gl::TextureFont::DrawOptions opts;
		opts.pixelSnap(true);

		ci::vec2 textSize = guiFont->measureString(text);

		ci::gl::pushMatrices(); {
			ci::gl::color(P_TEXT_COLOR);

			if (align == FontAlignment::ALIGN_RIGHT){
                guiFont->drawString(text, ci::vec2(-textSize.x, 0) + pos + ci::vec2(0,emHeight), opts);
			}
			else if (align == FontAlignment::ALIGN_CENTER){
                guiFont->drawString(text, ci::vec2((int)textSize.x*-0.5, 0) + pos + ci::vec2(0,emHeight), opts);
			}
			else{
				guiFont->drawString(text, pos + vec2(0,emHeight), opts);
			}
		}ci::gl::popMatrices();
	}

	void PretzelGlobal::renderText(std::string text, ci::vec2 pos) {
		renderTextInternal(text, pos, FontAlignment::ALIGN_LEFT);
	}

	void PretzelGlobal::renderTextRight(std::string text, ci::vec2 pos) {
		renderTextInternal(text, pos, FontAlignment::ALIGN_RIGHT);
	}

	void PretzelGlobal::renderTextCentered(std::string text, ci::vec2 pos) {
		renderTextInternal(text, pos, FontAlignment::ALIGN_CENTER);
	}
    
    ci::gl::TextureRef PretzelGlobal::getTextureFromSkin( ci::Rectf rect ){
        Surface srf( rect.getWidth(), rect.getHeight(), true);
        srf.copyFrom( mSkinSurf, Area(rect.x1, rect.y1, rect.x2, rect.y2), vec2(-rect.x1, -rect.y1) );
        return ci::gl::Texture::create( srf );
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
#endif
#if defined( CINDER_MSW )
		switch (type)
		{
			case CursorType::ARROW :
				::SetCursor( mCursorArrow );
				break;
			case CursorType::IBEAM :
                ::SetCursor( mCursorIBeam );
                break;
			case CursorType::HAND :
                ::SetCursor( mCursorHand );
                break;
			case CursorType::RESIZE_RL :
				::SetCursor( mCursorResize );
                break;
			default:
				break;
		}
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
    
    void PretzelGlobal::addSaveParam(std::string name, ci::vec2 *val){
		addParamInternal(name, val, _VEC2);
	}
    
    void PretzelGlobal::addSaveParam(std::string name, ci::vec3 *val){
		addParamInternal(name, val, _VEC3);
	}
    
    void PretzelGlobal::addSaveParam(std::string name, ci::Color *val){
		addParamInternal(name, val, _COLOR);
	}
    
    void PretzelGlobal::addSaveParam(std::string name, ci::ColorA *val){
		addParamInternal(name, val, _COLORA);
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
			appPath = getAppPath() / "guiSettings";

			if (!fs::exists(appPath)){
				CI_LOG_W( "Pretzel :: " ) << appPath << " does not exist. Creating it.";
				fs::create_directory(appPath);
			}
			appPath /= "settings.json";
		}

		JsonTree pSettings = JsonTree::makeObject("pretzelSettings");
		std::string tmp;
		for (int i = 0; i < mParamList.size(); i++){
			switch (mParamList[i].type){
                case _FLOAT:{
                    pSettings.pushBack(JsonTree(mParamList[i].name, toString(*(float*)mParamList[i].value)));
                    break;
                }case _INT:{
                    pSettings.pushBack(JsonTree(mParamList[i].name, toString(*(int*)mParamList[i].value)));
                    break;
                }case _BOOL:{
                    tmp = ((*(bool*)mParamList[i].value) == true) ? "1" : "0";
                    pSettings.pushBack(JsonTree(mParamList[i].name, tmp));
                    break;
                }case _STRING:{
                    pSettings.pushBack(JsonTree(mParamList[i].name, (*(std::string*)mParamList[i].value)));
                    break;
                }case _VEC2:{
                    JsonTree tt;
                    tt = tt.makeArray(mParamList[i].name);
                    tt.pushBack( JsonTree("x", toString(((vec2*)mParamList[i].value)->x)) );
                    tt.pushBack( JsonTree("y", toString(((vec2*)mParamList[i].value)->y)) );
                    pSettings.pushBack( tt );
                    break;
                }case _VEC3:{
                    JsonTree tt;
                    tt = tt.makeArray(mParamList[i].name);
                    tt.pushBack( JsonTree("x", toString(((vec3*)mParamList[i].value)->x)) );
                    tt.pushBack( JsonTree("y", toString(((vec3*)mParamList[i].value)->y)) );
                    tt.pushBack( JsonTree("z", toString(((vec3*)mParamList[i].value)->z)) );
                    pSettings.pushBack( tt );
                    break;
                }case _COLOR:{
                    JsonTree tt;
                    tt = tt.makeArray(mParamList[i].name);
                    tt.pushBack( JsonTree("r", toString(((Color*)mParamList[i].value)->r)) );
                    tt.pushBack( JsonTree("g", toString(((Color*)mParamList[i].value)->g)) );
                    tt.pushBack( JsonTree("b", toString(((Color*)mParamList[i].value)->b)) );
                    pSettings.pushBack( tt );
                    break;
                }case _COLORA:{
                    JsonTree tt;
                    tt = tt.makeArray(mParamList[i].name);
                    tt.pushBack( JsonTree("r", toString(((ColorA*)mParamList[i].value)->r)) );
                    tt.pushBack( JsonTree("g", toString(((ColorA*)mParamList[i].value)->g)) );
                    tt.pushBack( JsonTree("b", toString(((ColorA*)mParamList[i].value)->b)) );
                    tt.pushBack( JsonTree("a", toString(((ColorA*)mParamList[i].value)->a)) );
                    pSettings.pushBack( tt );
                    break;
                }default: {
                    break;
                }
			}
		}

		JsonTree root;
		root.pushBack(pSettings);
		root.write(appPath, JsonTree::WriteOptions());
        
        signalOnSettingsSave.emit();
	}

	void PretzelGlobal::loadSettings(fs::path settingsPath){
		fs::path loadPath = settingsPath;
		if (loadPath.string() == ""){
			loadPath = getAppPath() / "guiSettings" / "settings.json";
		}

		if (!fs::exists(loadPath)){
			CI_LOG_W("Pretzel :: Can't load ") << loadPath << " Path does not exist.";
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
                case _VEC2:
                    if (appSettings.hasChild(pName)){
                        vec2 p;
                        p.x = appSettings.getChild(pName).getChild("x").getValue<float>();
                        p.y = appSettings.getChild(pName).getChild("y").getValue<float>();
                        *((vec2*)mParamList[i].value) = p;
                    }
                    break;
                case _VEC3:
                    if (appSettings.hasChild(pName)){
                        vec3 p;
                        p.x = appSettings.getChild(pName).getChild("x").getValue<float>();
                        p.y = appSettings.getChild(pName).getChild("y").getValue<float>();
                        p.z = appSettings.getChild(pName).getChild("z").getValue<float>();
                        *((vec3*)mParamList[i].value) = p;
                    }
                    break;
                case _COLOR:
                    if (appSettings.hasChild(pName)){
                        Color p;
                        p.r = appSettings.getChild(pName).getChild("r").getValue<float>();
                        p.g = appSettings.getChild(pName).getChild("g").getValue<float>();
                        p.b = appSettings.getChild(pName).getChild("b").getValue<float>();
                        *((Color*)mParamList[i].value) = p;
                    }
                    break;
                case _COLORA:
                    if (appSettings.hasChild(pName)){
                        ColorA p;
                        p.r = appSettings.getChild(pName).getChild("r").getValue<float>();
                        p.g = appSettings.getChild(pName).getChild("g").getValue<float>();
                        p.b = appSettings.getChild(pName).getChild("b").getValue<float>();
                        p.a = appSettings.getChild(pName).getChild("a").getValue<float>();
                        *((ColorA*)mParamList[i].value) = p;
                    }
                    break;
				default:
					CI_LOG_W( "Pretzel :: Unrecognized settings type.");
					break;
				}
			}
		}
        signalOnSettingsLoad.emit();
	}

//    void PretzelGlobal::drawSolidRect( ci::Rectf rect )
//    {
//        gl::pushMatrices();
//        gl::translate( rect.x1, rect.y1 );
//        gl::scale( rect.getWidth(), rect.getHeight() );
////        getWindowData( getWindow() )->mSolidRectBatch->draw();
//        gl::popMatrices();
//    }
//    
//    void PretzelGlobal::drawStrokedRect( ci::Rectf rect )
//    {
//        gl::pushMatrices();
//        gl::translate( rect.x1, rect.y1 );
//        gl::scale( rect.getWidth(), rect.getHeight() );
//        
////        getWindowData( getWindow() )->mStrokedRectBatch->draw();
//        gl::popMatrices();
//    }
//    
//    void PretzelGlobal::drawLine( ci::vec2 start, ci::vec2 end )
//    {
//        gl::pushMatrices();
//        gl::translate(start);
//        gl::rotate( atan2( end.y-start.y, end.x-start.x ) );
//        gl::scale( vec2( glm::length(end - start) ) );
////        getWindowData( getWindow() )->mLineBatch->draw();
//        gl::popMatrices();
//    }

}
