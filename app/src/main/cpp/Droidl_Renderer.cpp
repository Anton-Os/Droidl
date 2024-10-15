#include "Droidl_Renderer.hpp"

Droidl_Renderer::~Droidl_Renderer() {
    /* glDeleteBuffers(MAX_RENDERID, _bufferSlots);
    glDeleteVertexArrays(MAX_RENDERID, _vertexArraySlots);
    glDeleteTextures(MAX_RENDERID, _textureSlots); */
    // TODO: Do EGL Specific cleanup
}

void Droidl_Renderer::init(NATIVE_WINDOW window) {
    logMessage("init triggered");

    int configCount;
    EGLint const eglAttribs[] = {
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_NONE
    };

    _platformCtx->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(_platformCtx->display, NULL, NULL);
    eglChooseConfig(_platformCtx->display, eglAttribs, &_platformCtx->config, 1, &configCount);

    _platformCtx->window = window;
    _platformCtx->surface = eglCreateWindowSurface(_platformCtx->display, _platformCtx->config, _platformCtx->window, NULL);
    eglMakeCurrent(_platformCtx->display, _platformCtx->surface, _platformCtx->surface, _platformCtx->eglCtx);

    Topl_Renderer_GL4::init(window);
}

void Droidl_Renderer::clear() {
    logMessage("clear triggered");
    Topl_Renderer_GL4::clear();
}

void Droidl_Renderer::setViewport(const Topl_Viewport* viewport) {
    logMessage("set viewport triggered");
    Topl_Renderer_GL4::setViewport(viewport);
}

void Droidl_Renderer::swapBuffers(double frameTime) {
    // eglSwapBuffers() // TODO: Perform Swap buffers for EGL
}

void Droidl_Renderer::build(const Geo_Actor* actor){
    logMessage("build triggered");
    Topl_Renderer_GL4::build(actor);
}

void Droidl_Renderer::update(const Geo_Actor* actor){
    logMessage("update triggered");
    Topl_Renderer_GL4::update(actor);
}

void Droidl_Renderer::setDrawMode(enum DRAW_Mode mode) {
    logMessage("set draw mode triggered");
    Topl_Renderer_GL4::setDrawMode(mode);
}

void Droidl_Renderer::draw(const Geo_Actor* actor) {
    logMessage("draw triggered");
    Topl_Renderer_GL4::draw(actor);
}

#ifdef RASTERON_H

Img_Base Droidl_Renderer::frame() {
    unsigned viewportHeight = Platform::getViewportHeight(_platformCtx->window);
    unsigned viewportWidth = Platform::getViewportWidth(_platformCtx->window);

	Rasteron_Image* stageImage = RASTERON_ALLOC("frame", viewportWidth, viewportHeight);
	glReadPixels(0, 0, viewportHeight, viewportWidth, GL_RGBA, GL_UNSIGNED_BYTE, stageImage->data);

	Rasteron_Image* flipImage = flipImgOp(stageImage, FLIP_Upside); // flipping image over
	Rasteron_Image* mirrorImage = mirrorImgOp(flipImage); // mirroring left and right sides
	bitSwitch_RB(mirrorImage->data, viewportHeight * viewportWidth); // flipping red and blue bits

	_frameImage = Img_Base();
	_frameImage.setImage(mirrorImage);
	RASTERON_DEALLOC(stageImage); RASTERON_DEALLOC(flipImage); RASTERON_DEALLOC(mirrorImage);
	return _frameImage;
}

void Droidl_Renderer::attachTexAt(const Rasteron_Image* image, unsigned renderID, unsigned binding) {
	GLuint textureTarget = *(_textureSlots + _textureIndex);
	_textureIndex++; // increments to next available slot

	for (std::vector<Texture_GL4>::iterator tex = _textures.begin(); tex != _textures.end(); tex++) {
		if (tex->renderID == renderID && tex->binding == binding && tex->format == TEX_2D) { // multi-texture substitution
			textureTarget = tex->texture;
			if (_textureIndex > 1) _textureIndex--; // decrement if texture binding is located
		}
	}

	glActiveTexture(GL_TEXTURE0 + binding);
	glBindTexture(GL_TEXTURE_2D, textureTarget);

	GL4::setTextureProperties(GL_TEXTURE_2D, _texMode);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->height, image->width, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (*(_textureSlots + _textureIndex - 1) == textureTarget)
		_textures.push_back(Texture_GL4(renderID, (unsigned short)binding, TEX_2D, _texMode, textureTarget)); // multi-texture addition
}

void Droidl_Renderer::attachTex3D(const Img_Volume* volumeTex, unsigned renderID) {
	GLuint textureTarget = *(_textureSlots + _textureIndex);
	_textureIndex++; // increments to next available slot

	for (std::vector<Texture_GL4>::iterator tex = _textures.begin(); tex != _textures.end(); tex++) {
		if (tex->renderID == renderID && tex->format == TEX_3D) {
			textureTarget = tex->texture;
			if (_textureIndex > 1) _textureIndex--; // decrement since texture binding is located
		}
	}

	glActiveTexture(GL_TEXTURE0 + MAX_TEX_BINDINGS);
	glBindTexture(GL_TEXTURE_3D, textureTarget);

	const Img_Base* volumeTexImage = volumeTex->getVolumeImg();
	GL4::setTextureProperties(GL_TEXTURE_3D, _texMode);
	glTexImage3D(
		GL_TEXTURE_3D,
		0, GL_RGBA,
		volumeTex->getWidth(),
		volumeTex->getHeight(),
		volumeTex->getDepth(),
		0, GL_RGBA,
		GL_UNSIGNED_BYTE,
		volumeTexImage->getImage()->data
	);
	glGenerateMipmap(GL_TEXTURE_3D);

	if (*(_textureSlots + _textureIndex - 1) == textureTarget)
		_textures.push_back(Texture_GL4(renderID, TEX_3D, _texMode, textureTarget));
}

#endif
