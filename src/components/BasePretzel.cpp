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

namespace pretzel
{
	BasePretzel::BasePretzel() :
        mParent(NULL),
        type(WidgetType::UNINITALIZED),
        mOffset(0,0),
        mBounds(0,0,0,0)
    {
		mGlobal = pretzel::PretzelGlobal::getInstance();
	}
    
    BasePretzel::~BasePretzel(){
        
    }

	void BasePretzel::registerPretzel(BasePretzel *child){
        child->setParent( this );
        
		mPretzelChildren.push_back(child);
		updateChildrenBounds();
	}

	// -------------------------------------------------------
	void BasePretzel::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds)
    {
		mOffset = vec2(offset);
		mParentBounds = parentBounds;

		mBounds.x2 = parentBounds.getWidth();
        
//        mGlobalOffset = vec2( mGlobal->getGlobalPos() );
	}

	// -------------------------------------------------------------
    BasePretzel* BasePretzel::getParent()
    {
        return mParent;
    };
    
    void BasePretzel::setParent( BasePretzel *parent )
    {
        mParent = parent;
    }
    
    ci::Rectf BasePretzel::getBounds(){
        return mBounds;
    }
    
	ci::Rectf BasePretzel::getGlobalBounds() {
        Rectf bb(mBounds);
        bb.offset( mGlobalOffset );
		return bb;
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
    void BasePretzel::mouseWheel(const float increment){
        for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
            (*it)->mouseWheel(increment);
        }
    }
	void BasePretzel::keyDown(const char &key, const int &keyCode){
		for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
            (*it)->keyDown(key, keyCode);
		}
	}
    
    void BasePretzel::update()
    {
        for (vector<BasePretzel*>::const_iterator it = mPretzelChildren.begin(); it != mPretzelChildren.end(); ++it){
            (*it)->update();
        }
    }
    

}
