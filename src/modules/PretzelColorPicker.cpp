//
//  PretzelColorPicker.cpp
//  BasicSample
//
//  Created by Charlie Whitney on 6/30/14.
//
//

#include "PretzelColorPicker.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace pretzel{
    
	PretzelColorPicker::PretzelColorPicker(BasePretzel *parent, std::string label, ci::Color *value) :
        bUseAlpha(false),
        bExpanded(false),
        bHover(false),
        bDragging(false),
		bDraggingHue(false),
        mArrowRotation(0),
        mHueCol(1,0,0),
        mHueNorm(0.0),
        BasePretzel()
    {
        mBounds.set(0, 0, 200, 23);        
		mLabel = label;
        mColor = value;
        mLastColor = *value;
        type = WidgetType::COLOR_PICKER;
        
        setup();
        mGlobal->addSaveParam(label, value);
        parent->registerPretzel(this);
    }
    
	PretzelColorPicker::PretzelColorPicker(BasePretzel *parent, std::string label, ci::ColorA *value) :
        bUseAlpha(true),
        bExpanded(false),
        bHover(false),
        bDragging(false),
		bDraggingHue(false),
        mArrowRotation(0),
        mHueCol(1,0,0),
        mHueNorm(0.0),
        BasePretzel()
    {
		mBounds.set(0, 0, 200, 23);
		mLabel = label;
        mColorA = value;
        mLastColor = *value;
        type = WidgetType::COLOR_PICKER;
        
        setup();
        mGlobal->addSaveParam(label, value);
		parent->registerPretzel(this);
	}
    
    void PretzelColorPicker::setup()
    {
        // load images
        mArrowTex = mGlobal->getTextureFromSkin( Rectf(28, 0, 42, 12) );
        mCrosshairTex = mGlobal->getTextureFromSkin( Rectf(44, 0, 52, 8) );
        
        mHueSurf = ci::Surface( loadImage( loadResource(PRETZEL_HSL_BAR) ) );
        mHueStrip = gl::Texture::create( mHueSurf );
        
        mBoxFbo = gl::Fbo::create(256, 256);
        
        PretzelShaders ps;
        mBoxShader = gl::GlslProg::create( ps.hueVert, ps.hueFrag );
        
        // set rects
        mCollapsedRect.set(0, 0, mBounds.getWidth(), 23);
        mExpandedRect.set( 0, 0, mBounds.getWidth(), 23+150);
        
        int boxW = 36, boxH = 19;
        mColorPickRect = Rectf( mBounds.x2 - boxW, 0, mBounds.x2, boxH );
        mColorPickRect.offset( vec2(-10, -1) );
        
        int swatchSize = 150;
        mColorSwatchRect = Rectf(mColorPickRect.x2 - swatchSize, mColorPickRect.y2, mColorPickRect.x2, mColorPickRect.y2 + swatchSize);
        mColorSwatchRect.offset( vec2(-1,1) );
        
        Surface checkerSurf( mColorPickRect.getWidth(), mColorPickRect.getHeight(), false);
        ip::fill(&checkerSurf, Color(1,1,1) );
        
        // draw the checkboard pattern
        gl::color(Color::white());
        gl::drawSolidRect(mColorPickRect);
        for( int k=0; k<mColorPickRect.getHeight(); k+=4){
            int i = ((k/4)%2) * 4;
            for( ; i<mColorPickRect.getWidth(); i+=8){
                Rectf tmp(0,0,4,4);
                tmp.offset( vec2(i, k) );
                ip::fill(&checkerSurf, Color::gray(198.0/255.0), Area(tmp));
            }
        }

        mCheckerPat = gl::Texture::create(checkerSurf);
        mCrosshairPos = vec2(0,0);
        
        redrawHueBox();
        getColorAtPos( mCrosshairPos );
    }
    
    void PretzelColorPicker::redrawHueBox()
    {
        ColorA cc = mHueSurf.getPixel( vec2(1, mHueNorm * mHueSurf.getHeight()) );
        mHueCol = cc;
        
        gl::ScopedMatrices scMat;
        gl::ScopedGlslProg scS( mBoxShader );
        gl::ScopedViewport scVp( mBoxFbo->getSize() );
        gl::setMatricesWindow( mBoxFbo->getSize() );
        gl::ScopedFramebuffer scF( mBoxFbo );
        
        mBoxShader->uniform( "uPickedCol", mHueCol );
        
        gl::clear( ColorA(1,1,1,0) );
        gl::drawSolidRect( mBoxFbo->getBounds() );
    
    }
    
    void PretzelColorPicker::mouseDown(const ci::vec2 &pos)
    {
        if( !bExpanded && mCollapsedRect.contains( pos - mOffset ) ){
            expand();
        }
        else if(bExpanded && mCollapsedRect.contains( pos - mOffset )){
            contract();
        }
        else if( bExpanded && mColorSwatchRect.contains(pos - mOffset)){
            vec2 localPos = pos - mOffset;
            mCrosshairPos.x = ci::math<float>::clamp( (localPos.x - mColorSwatchRect.x1) / mColorSwatchRect.getWidth(), 0.0, 1.0);
            mCrosshairPos.y = ci::math<float>::clamp( (localPos.y - mColorSwatchRect.y1) / mColorSwatchRect.getHeight(), 0.0, 1.0);
            bDragging = true;
            
            getColorAtPos( mCrosshairPos );
        }
        else if( bExpanded && mHueStripRect.contains(pos - mOffset) ){
            vec2 localPos = pos - mOffset;
            mHueNorm = lmap( localPos.y, mHueStripRect.y1, mHueStripRect.y2, 0.0f, 1.0f);
            mHueNorm = ci::math<float>::clamp(mHueNorm);
            bDraggingHue = true;
            
            redrawHueBox();
            getColorAtPos( mCrosshairPos );
        }
    }
    
    void PretzelColorPicker::mouseDragged(const ci::vec2 &pos)
    {
        if( bDragging ){
            vec2 localPos = pos - mOffset;
            mCrosshairPos.x = ci::math<float>::clamp( (localPos.x - mColorSwatchRect.x1) / mColorSwatchRect.getWidth(), 0.0, 1.0);
            mCrosshairPos.y = ci::math<float>::clamp( (localPos.y - mColorSwatchRect.y1) / mColorSwatchRect.getHeight(), 0.0, 1.0);
            
            getColorAtPos( mCrosshairPos );
        }
        else if( bDraggingHue ){
            vec2 localPos = pos - mOffset;
            mHueNorm = lmap( localPos.y, mHueStripRect.y1, mHueStripRect.y2, 0.0f, 1.0f);
            mHueNorm = ci::math<float>::clamp(mHueNorm);
            
            redrawHueBox();
            getColorAtPos( mCrosshairPos );
        }
    }
    
    void PretzelColorPicker::mouseUp(const ci::vec2 &pos){
        bDragging = false;
        bDraggingHue = false;
    }
    
    void PretzelColorPicker::mouseMoved(const ci::vec2 &pos)
    {
        if( mCollapsedRect.contains(pos-mOffset) ){
            bHover = true;
            mGlobal->setCursor( CursorType::HAND );
        }else if( bExpanded && mColorSwatchRect.contains(pos-mOffset)){
            bHover = true;
            mGlobal->setCursor( CursorType::HAND );
        }
        else{
            if(bHover){
                bHover = false;
                mGlobal->setCursor( CursorType::ARROW );
            }
        }
    }
    
    ColorA PretzelColorPicker::getColorAtPos( vec2 crosshairPos )
    {
        ivec2 pos = vec2(mBoxFbo->getSize() - ivec2(1)) * crosshairPos;
        
        // pick the color off a buffer
        mBoxFbo->bindFramebuffer();
        gl::readBuffer( GL_FRAMEBUFFER );
        unsigned char pixel[4];
        gl::readPixels( pos.x, mBoxFbo->getHeight() - 1 - pos.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        ColorA tmp( (float)pixel[0] / 255.0, (float)pixel[1] / 255.0, (float)pixel[2] / 255.0, 1.0);
        mBoxFbo->unbindFramebuffer();
        
        // set it back to the current color
        if( bUseAlpha ){
            *mColorA = tmp;
            mLastColor = *mColorA;
        }else {
            *mColor = tmp;
            mLastColor = *mColor;
        }
        
        return tmp;
    }

    
    void PretzelColorPicker::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds)
    {
        BasePretzel::updateBounds(offset, parentBounds);
        
        // top small info box
        int boxW = 36, boxH = 19;
        mColorPickRect = Rectf( mBounds.x2 - boxW, 0, mBounds.x2, boxH );
        mColorPickRect.offset( vec2(-10, -1) );
        
        // long skinny strip
        int sW = 19;
        mHueStripRect = Rectf( 10, mColorSwatchRect.y1, sW + 10, mColorSwatchRect.y2 );
        
        // large picker box
        int swatchSize = 150;
        mColorSwatchRect = Rectf( mHueStripRect.x2 + 10, mColorPickRect.y2, mHueStripRect.x2 + 10 + swatchSize, mColorPickRect.y2 + swatchSize);
        mColorSwatchRect.offset( vec2(-1,1) );
        
        mCollapsedRect.set(0, 0, mBounds.getWidth(), 23);
        mExpandedRect.set(0, 0, mBounds.getWidth(), 150+23);
    }
    
    void PretzelColorPicker::expand()
    {
        mBounds = mExpandedRect;
        timeline().apply(&mArrowRotation, 90.0f, 0.1f);
        bExpanded = true;
        
        BasePretzel *bp = mParent;
        while( bp->getParent() != NULL ){
            bp = bp->getParent();
        }
        bp->updateChildrenBounds();
    }
    
    void PretzelColorPicker::contract()
    {
        mBounds = mCollapsedRect;
        timeline().apply(&mArrowRotation, 0.0f, 0.1f);
        bExpanded = false;
        
        BasePretzel *bp = mParent;
        while( bp->getParent() != NULL ){
            bp = bp->getParent();
        }
        bp->updateChildrenBounds();
    }
    
    void PretzelColorPicker::getCrosshairPosFromCol()
    {
        ci::ColorA col;
        if( bUseAlpha ){ col = *mColorA; }
        else { col = ColorA(*mColor, 1.0); }
        
        vec3 hsvCol = rgbToHsv( col );
        
        mCrosshairPos.x = hsvCol.y;
        mCrosshairPos.y = 1.0 - hsvCol.z;
        
        mHueNorm = 1.0 - hsvCol.x;
    }
    
    void PretzelColorPicker::update()
    {
        if( !bDragging && !bDraggingHue ){
            if( bUseAlpha && mLastColor != *mColorA){
                mLastColor = *mColorA;
                getCrosshairPosFromCol();
                redrawHueBox();
            }else if( !bUseAlpha && mLastColor != *mColor){
                mLastColor = *mColor;
                getCrosshairPosFromCol();
                redrawHueBox();
            }
        }
    }
    
	void PretzelColorPicker::draw()
    {
		gl::pushMatrices(); {
			gl::translate(mOffset + vec2(0,2));
            
            // TOP ------------------------------------------------------------
            
            gl::color(1,1,1,1);
            if( mArrowTex ){
                gl::pushMatrices();{
                    gl::translate( vec2(14, 8) );
                    gl::rotate( toRadians( mArrowRotation ) );
                    gl::translate( floor(mArrowTex->getWidth() * -0.5), floor(mArrowTex->getHeight() * -0.5) );
                    gl::draw( mArrowTex );
                }gl::popMatrices();
            }
            
            // checkered bg
            gl::draw(mCheckerPat, mColorPickRect.getUpperLeft() );
            
            // color
            if( bUseAlpha ){ gl::color( *mColorA ); }
            else { gl::color(*mColor); }
			PWindow()->drawSolidRect(mColorPickRect);
            
            // outline
            gl::color( mGlobal->P_OUTLINE_COLOR );
//            PWindow()->drawStrokedRect(mColorPickRect);

			mGlobal->renderText(mLabel, vec2(25, 1));
            
            // BOTTOM ------------------------------------------------------------
            if(bExpanded){
                gl::color( ColorA(1, 1, 1, 1 ) );
                
                gl::draw( mHueStrip, mHueStripRect );
                gl::drawLine( vec2(mHueStripRect.x1 - 3, mHueStripRect.y1 + mHueStripRect.getHeight() * mHueNorm),
                              vec2(mHueStripRect.x2 + 3, mHueStripRect.y1 + mHueStripRect.getHeight() * mHueNorm) );
                
                gl::draw(mBoxFbo->getColorTexture(), mColorSwatchRect);
                gl::draw(mCrosshairTex,
                         mColorSwatchRect.getUpperLeft() + (mCrosshairPos * mColorSwatchRect.getSize()) -
                         ( vec2(mCrosshairTex->getSize()) * 0.5f ) ); //* 0.5f
            }
            
		}gl::popMatrices();
	}
}
