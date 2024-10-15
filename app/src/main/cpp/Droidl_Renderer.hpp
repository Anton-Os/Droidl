#include "Topl_Renderer.hpp"

#include "backends/opengl/Topl_Renderer_GL4.hpp"

class Droidl_Renderer : public Topl_Renderer_GL4 {
public:
    Droidl_Renderer(NATIVE_PLATFORM_CONTEXT* context) : Topl_Renderer_GL4(context) {}
    virtual ~Droidl_Renderer();

    void draw(const Geo_Actor* actor) override;
    void clear() override;
    void setViewport(const Topl_Viewport* viewport) override;
    void swapBuffers(double frameTime) override;
    void setDrawMode(enum DRAW_Mode mode) override;

#ifdef RASTERON_H
    Img_Base frame() override;
#endif
protected:
    void init(NATIVE_WINDOW window) override;
    void update(const Geo_Actor* actor) override;
    void build(const Geo_Actor* actor) override;
#ifdef RASTERON_H
    void attachTexAt(const Rasteron_Image* image, unsigned renderID, unsigned binding) override;
	void attachTex3D(const Img_Volume* volumeTex, unsigned id) override;
#endif
    Topl_Pipeline_GL4* _pipeline;

    std::map<unsigned long, VertexArray_GL4> _vertexArrayMap;
    std::map<unsigned long, Buffer_GL4> _vertexBufferMap, _indexBufferMap, _blockBufferMap;
    std::vector<Texture_GL4> _textures; // active textures
    std::map<unsigned long, Texture_GL4[MAX_TEX_BINDINGS + 2]> _textureMap; // TODO: Change to this type
// private:
    GLenum _drawMode_GL4; // OpenGL specific draw mode
    GLuint* _bufferSlots;
    unsigned _bufferIndex = 0; // increments to indicate next available buffer slot
    GLuint* _vertexArraySlots;
    unsigned _vertexArrayIndex = 0; // increments to indicate next available vertex array slot
    GLuint* _textureSlots;
    unsigned _textureIndex = 0; // increments to indicate next available texture slot
};