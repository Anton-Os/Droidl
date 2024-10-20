#include "Topl_Renderer.hpp"

#include "backends/opengl/Topl_Renderer_GL4.hpp"

#ifndef LOGI
#define LOGI(...) \
    ((void)logMessage(__VA_ARGS__))
#endif
#ifndef LOGE
#define LOGE(...) \
    ((void)logMessage(MESSAGE_Exclaim, __VA_ARGS__))
#endif

namespace EGL {
    std::string getError(GLint error);
}

class Droidl_Renderer : public Topl_Renderer_GL4 {
public:
    Droidl_Renderer(NATIVE_PLATFORM_CONTEXT* context) : Topl_Renderer_GL4(context) {
        _flags[DRAW_ORDER_BIT] = DRAW_NORMAL;
        init(context->window);

        setViewport(&_defaultViewport); // viewport creation
        setDrawMode(DRAW_Triangles);
    }
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
    std::string getLastError() const { return EGL::getError(errorCode); }
private:
    std::pair<int, int> eglVersion;
    EGLint errorCode;
};