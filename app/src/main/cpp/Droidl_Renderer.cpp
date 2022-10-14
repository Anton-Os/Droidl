#include "Droidl_Renderer.hpp"

#include "Droidl_Renderer.hpp"

void Droidl_Renderer::init(NATIVE_WINDOW window) {
    // Implement initialization
}

void Droidl_Renderer::clearView(){
    // Implement clearing operation
}

void Droidl_Renderer::setViewport(const Topl_Viewport* viewport) {
    // Implement viewport setting
}

void Droidl_Renderer::switchFramebuff(){
    // Implement framebuffer switching operation
    _isDrawn = false;
}

void Droidl_Renderer::build(const Topl_Scene* scene) {
    // Implement building operation
    _isBuilt = true;
}

#ifdef RASTERON_H

Rasteron_Image* Droidl_Renderer::frame() {
	Rasteron_Image* image = createSolidImg({ TOPL_WIN_HEIGHT, TOPL_WIN_WIDTH }, CLEAR_COLOR_HEX);
	return image;
}

void Droidl_Renderer::texturize(const Topl_Scene* scene) {
	// Implement texturizing operations
}

void Droidl_Renderer::attachTexture(const Rasteron_Image* image, unsigned id){
	// Implement texture attaching
}

void Droidl_Renderer::attachMaterial(const Img_Material* material, unsigned id) {
	// Implement Body
}

#endif

void Droidl_Renderer::update(const Topl_Scene* scene){
    // Implement update operations
}

void Droidl_Renderer::drawMode(){
    switch(_drawMode) {
        case DRAW_Points: break;
        case DRAW_Lines: break;
        case DRAW_Triangles: break;
        case DRAW_Fan: break;
        case DRAW_Strip: break;
        default: return logMessage(MESSAGE_Exclaim, "Draw type not supported yet!");
    }
}

/* void Droidl_Renderer::render(const Topl_Scene* scene){
	// Implement render operation
	_isDrawn = true;
} */

void Droidl_Renderer::renderTarget(unsigned long renderID){
    // if(renderID == SPECIAL_SCENE_RENDER_ID) { }
    // else {}
}