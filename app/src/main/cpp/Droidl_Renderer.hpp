#include "Topl_Renderer.hpp"

class Droidl_Renderer : public Topl_Renderer { // TODO: Inherit from Topl_Renderer
public:
    Droidl_Renderer(NATIVE_WINDOW window) : Topl_Renderer(window) {
        _isDrawInOrder = REGULAR_DRAW_ORDER;
        init(window);
    }
    ~Droidl_Renderer();

    void clearView() override;
    void setViewport(const Topl_Viewport* viewport) override;
    void switchFramebuff() override;
    void build(const Topl_Scene* scene) override;
    void texturize(const Topl_Scene* scene) override;

    void setPipeline(Topl_Pipeline_GL4* pipeline);
    void genPipeline(Topl_Pipeline_GL4* pipeline, entry_shader_cptr vertexShader, shader_cptr pixelShader);
    void genPipeline(Topl_Pipeline_GL4* pipeline, entry_shader_cptr vertexShader, shader_cptr geomShader, shader_cptr pixelShader, shader_cptr tessCtrlShader, shader_cptr tessEvalShader);
#ifdef RASTERON_H
    Rasteron_Image* frame() override;
#endif
private:
    void init(NATIVE_WINDOW window) override;
    // void init(NATIVE_WINDOW window, std::initializer_list<Topl_Viewport> viewports) override;
    void update(const Topl_Scene* scene) override;
    void drawMode(void) override;
    // void render(const Topl_Scene* scene) override;
    void renderTarget(unsigned long renderID) override;
#ifdef RASTERON_H
    void attachTexture(const Rasteron_Image* image, unsigned id) override;
	void attachMaterial(const Topl_Material* material, unsigned id) override;
#endif
    // Buffer_GL4* findBuffer(BUFF_Type type, unsigned long renderID);

    // Topl_Pipeline_GL4* _pipeline;

    /* GLenum _drawMode_GL4; // OpenGL specific draw mode
    GLuint _bufferSlots[GL4_BUFFER_MAX]; // stores all buffers
    unsigned _bufferIndex = 0; // increments to indicate next available buffer slot
    std::vector<Buffer_GL4> _buffers; // active buffers
    GLuint _vertexArraySlots[GL4_VERTEX_ARRAY_MAX]; // stores all vertex arrays
    unsigned _vertexArrayIndex = 0; // increments to indicate next available vertex array slot
    std::vector<VertexArray_GL4> _vertexArrays; // active vertex arrays
    GLuint _textureSlots[GL4_TEXTURE_BINDINGS_MAX]; // stores all textures
    unsigned _textureIndex = 0; // increments to indicate next available texture slot
    std::vector<Texture_GL4> _textures; // active textures */
};