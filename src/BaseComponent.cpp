#include "BaseComponent.h"


using namespace ci;
using namespace std;

void BasePanel::BaseComponent(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
	mOffset.set(offset);
	mParentBounds = parentBounds;
}

ci::Rectf BaseComponent::getBounds() {
	return mBounds;
}

float BaseComponent::getWidth() {
	return mBounds.getWidth();
}

float BaseComponent::getHeight() {
	return mBounds.getHeight();
}

void BaseComponent::updateChildrenBounds() {

}