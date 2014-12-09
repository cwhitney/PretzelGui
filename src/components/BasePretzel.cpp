//
//  BasePretzel.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 2/4/14.
//
//

#include "BasePretzel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace Pretzel{
	BasePretzel::BasePretzel() : mParent(NULL) {
		mOffset = vec2(0, 0);
		mBounds.set(0, 0, 0, 0);

		mGlobal = Pretzel::PretzelGlobal::getInstance();
        type = WidgetType::UNINITALIZED;
	}
    
    BasePretzel::~BasePretzel(){
//        console() << "CLEAN UP. Offset is :: " << mOffset << endl;
    }

	void BasePretzel::registerPretzel(BasePretzel *child){
        child->setParent( this );
        
		mPretzelChildren.push_back(child);
		updateChildrenBounds();
	}

	// -------------------------------------------------------
	void BasePretzel::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds){
		mOffset = vec2(offset);
		mParentBounds = parentBounds;

		mBounds.x2 = parentBounds.getWidth();
        
        mGlobalOffset = vec2( mGlobal->getGlobalPos() );
	}

	// -------------------------------------------------------------
    BasePretzel* BasePretzel::getParent(){
        return mParent;
    };
    
    void BasePretzel::setParent( BasePretzel *parent ){
        mParent = parent;
    }
    
	ci::Rectf BasePretzel::getBounds() {
		return mBounds;
	}

	float BasePretzel::getWidth() {
		return mBounds.getWidth();
	}

	float BasePretzel::getHeight() {
		return mBounds.getHeight();
	}

	void BasePretzel::updateChildrenBounds() {

	}

	// -------------------------------------------------------------------
	void BasePretzel::mouseDown(const ci::vec2 &pos){
		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
			(*it)->mouseDown(pos);
		}
	}
	void BasePretzel::mouseDragged(const ci::vec2 &pos){
		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
			(*it)->mouseDragged(pos);
		}
	}
	void BasePretzel::mouseUp(const ci::vec2 &pos){
		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
			(*it)->mouseUp(pos);
		}
	}
	void BasePretzel::mouseMoved(const ci::vec2 &pos){
		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
			(*it)->mouseMoved(pos);
		}
	}
	void BasePretzel::keyDown(const char &key, const int &keyCode){
		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
			(*it)->keyDown(key, keyCode);
		}
	}

}