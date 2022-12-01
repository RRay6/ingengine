#include "engine.h"
#include <iostream>
#include <string>
#define SOKOL_IMPL
#define SOKOL_GLCORE33
#define SOKOL_NO_ENTRY
#include "sokol_app.h"

#include "sokol_gfx.h"
#include "sokol_fetch.h"
#include "sokol_glue.h"
#define SOKOL_GL_IMPL
#include "util/sokol_gl.h"
#include <stdio.h>  // needed by fontstash's IO functions even though they are not used
#define FONTSTASH_IMPLEMENTATION
#include "../external/fontstash-master/src/fontstash.h"
//#define SOKOL_FONTSTASH_IMPL
#include "util/sokol_fontstash.h"
#include "../external/dbgui/dbgui.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/vec3.hpp>
#include "glm/gtx/transform.hpp"

#include "uniforms.h"
#include "types.h"

#include "Components/sprite.h"

#include <vector>

typedef struct sfetch_range_t {
    void* ptr;
    size_t size;
} sfetch_range_t;

#define SFETCH_RANGE(x) sfetch_range_t{ &x, sizeof(x) }

using namespace std;


namespace graphics_manager
{
    struct Texture
    {
        sg_image image;
        int width;
        int height;
    };

    unordered_map<string, Texture> umap;

    typedef struct {
        FONScontext* fons;
        float dpi_scale;
        int font;
        uint8_t font_data[256 * 1024];
    } state_t;
    state_t state;

    FONScontext* context;

    sg_pipeline pipeline;
    sg_pass_action pass_action{};
    sg_bindings bindings{};
    sg_shader_desc shader_desc{};

    float lh;

   int MakePowerOfTwo(float ohDear) {
        unsigned int returning = (unsigned int)ohDear;
        unsigned int shifting = returning;
        int highestBitIndex = -1;
        int numOnes = 0;

        while (shifting > 0) {
            if (shifting % 2 == 1) {
                numOnes++;
            }
            shifting = shifting >> 1;
            highestBitIndex++;
        }

        if (highestBitIndex > 0 && numOnes > 1) {
            returning = 1;
            highestBitIndex++;
            returning = returning << highestBitIndex;
        }

        return returning;
    }

    void IsFontLoad(const sfetch_response_t* response) {
        if (response->fetched) {
            state.font = fonsAddFontMem(state.fons, "sans", (unsigned char*)response->buffer_ptr, (int)response->fetched_size, false);
        }
    }

    void init(void) {
        state.dpi_scale = sapp_dpi_scale();
        sg_desc sgd{};
        sgl_desc_t sgldt{ 0 };
        //sfons_desc_t sfonsDesT{};
        sfetch_desc_t sfetchDesT{};
        sfetch_request_t sfetchReqT{};

        sgd.context = sapp_sgcontext();

        sg_setup(&sgd);
        //__dbgui_setup(sapp_sample_count());

        sgl_setup(&sgldt);

        int atlas_dim = MakePowerOfTwo(512.0f * state.dpi_scale);

        //sfonsDesT.width = atlas_dim;
        //sfonsDesT.height = atlas_dim;
        context = sfons_create(atlas_dim, atlas_dim, FONS_ZERO_TOPLEFT);

        state.fons = context;
        state.font = FONS_INVALID;

        sfetchDesT.num_channels = 1;
        sfetchDesT.num_lanes = 4;

        sfetch_setup(&sfetchDesT);

        char path_buf[512];
        sfetchReqT.path = (ingengine::gameEngine.resources.ResolvePath("fonts", "DroidSerif-Regular.ttf")).string().c_str();
        sfetchReqT.callback = IsFontLoad;
        sfetchReqT.buffer_ptr = SFETCH_RANGE(state.font_data).ptr;

        sfetch_send(&sfetchReqT);


    }

    void frame(void) {


        float dpis = state.dpi_scale;

        sfetch_dowork();

        lh = 0;

        unsigned int white = sfons_rgba(255, 255, 255, 255);
        unsigned int blue = sfons_rgba(0, 192, 255, 255);
        unsigned int black = sfons_rgba(0, 0, 0, 255);

        fonsClearState(state.fons);

        sgl_defaults();
        sgl_matrix_mode_projection();
        sgl_ortho(0.0f, sapp_widthf(), sapp_heightf(), 0.0f, -1.0f, +1.0f);

        FONScontext* fs = state.fons;
        if (state.font != FONS_INVALID) {
            fonsSetFont(fs, state.font);
            fonsSetSize(fs, 24.0f * dpis);
            fonsVertMetrics(fs, NULL, NULL, &lh);
            fonsSetColor(fs, white);
            ingengine::gameEngine.entity_manager.ForEach<Types::Text>([&](ecs::EntityID entity) {
                Types::Text& theText = ingengine::gameEngine.entity_manager.Get<Types::Text>(entity);
                fonsDrawText(fs, theText.xPos * dpis, theText.yPos * dpis, theText.contents.c_str(), NULL);
                });

            //dx = fonsDrawText(fs, dx, dy, message.c_str(), NULL);
        }

        sfons_flush(fs);

        //sg_pass_action sgPass{};

        pass_action.colors[0].action = SG_ACTION_CLEAR;
        pass_action.colors[0].value = { 0.3f, 0.3f, 0.32f, 1.0f };

        sg_begin_default_pass(pass_action, sapp_width(), sapp_height());
        sgl_draw();
        sg_end_pass();
        sg_commit();
    }





    void GraphicsManager::Startup()
    {

        int window_width = 800;
        int window_height = 800;
        // std::string window_name = "ingengine";
        bool window_fullscreen = false;

        glfwInit();
        // We'll use sokol_gfx's OpenGL backend
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(window_width, window_height, "ingengine", window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
        glfwSetWindowAspectRatio(window, window_width, window_height);

        if (!window)
        {
            std::cerr << "Failed to create a window." << std::endl;
            //std::cout << "Failed to create a window.\n";
            glfwTerminate();
        }
        // else
        // {
        //     std::cerr << "It's good." << std::endl;
        // }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        //glfwPollEvents();

        glfwSetWindowSizeCallback(window, window_size_callback);

        glfwSetWindowCloseCallback(window, WindowClosed);


        sg_desc desc{};


        // A vertex buffer containing a textured square.
        const float vertices[] = {
            // positions      // texcoords
            -1.0f,  -1.0f,    0.0f,  0.0f,
            1.0f,  -1.0f,    1.0f,  0.0f,
            -1.0f,   1.0f,    0.0f,  1.0f,
            1.0f,   1.0f,    1.0f,  1.0f,
        };

        sg_buffer_desc buffer_desc{};
        buffer_desc.data = SG_RANGE(vertices);
        sg_buffer vertex_buffer = sg_make_buffer(buffer_desc);

        sg_pipeline_desc pipeline_desc{};
        pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;
        pipeline_desc.colors[0].blend.enabled = true;
        pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
        pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        pipeline_desc.depth.write_enabled = true;
        pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
        pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

        shader_desc.vs.source = R"(
    #version 330
    uniform mat4 projection;
    uniform mat4 transform;
    layout(location=0) in vec2 position;
    layout(location=1) in vec2 texcoords0;
    out vec2 texcoords;
    void main() {
        gl_Position = projection*transform*vec4( position, 0.0, 1.0 );
        texcoords = texcoords0;
    })";
        shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
        // The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
        shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
        shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
        shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
        shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;
        shader_desc.fs.source = R"(
        #version 330
        uniform sampler2D tex;
        in vec2 texcoords;
        out vec4 frag_color;
        void main() {
            frag_color = texture( tex, texcoords );
            // If we're not drawing back to front, discard very transparent pixels so we
            // don't write to the depth buffer and prevent farther sprites from drawing.
            if( frag_color.a < 0.1 ) discard;
        }
    )";
        shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
        shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;
        pipeline_desc.shader = sg_make_shader(shader_desc);
        pipeline = sg_make_pipeline(pipeline_desc);

        pass_action.colors[0].action = SG_ACTION_CLEAR;
        pass_action.colors[0].value = {  }; // SG_DEFAULT_CLEAR_RED, SG_DEFAULT_CLEAR_GREEN, SG_DEFAULT_CLEAR_BLUE, SG_DEFAULT_CLEAR_ALPHA
        //Magum::Math::Color4::from(pass_action.colors[0].value) = 0x1f1f1f_rgbf;

        bindings.vertex_buffers[0] = vertex_buffer;

    }

    void GraphicsManager::Update() {
        // if (!glfwWindowShouldClose(window)) {

        //     glfwSwapBuffers(window);
        //     glfwPollEvents();

        //     glfwSetWindowCloseCallback(window, WindowClosed);
        // }
    }

    void GraphicsManager::Shutdown() {
        sg_shutdown();
    }

    GLFWwindow* GraphicsManager::GetWindow() {
        return window;
    }

    void GraphicsManager::ShouldQuit() {
        //glfwSetWindowCloseCallback(window, glfwWindowCloseCallback(window));
        glfwWindowShouldClose(window);
    }

    void GraphicsManager::WindowClosed(GLFWwindow* window)
    {
        std::cerr << "Close." << std::endl;
        glfwSetWindowShouldClose(window, true);
        glfwTerminate();
        exit(0);
    }

    bool GraphicsManager::LoadImageA(const string& name, const string& path) //const string& name, const string& path
    {
        //std::string path_string{resources.ResolvePath("sounds", "click.wav").u8string()};

        int width, height, channels;

        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

        if (data == 0)
        {
            cout << "Error loading image file" << endl;
            return false;
        }

        sg_image image;

        sg_image_desc image_desc{};
        image_desc.width = width;
        image_desc.height = height;
        image_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
        image_desc.min_filter = SG_FILTER_LINEAR;
        image_desc.mag_filter = SG_FILTER_LINEAR;
        image_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
        image_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
        image_desc.data.subimage[0][0].ptr = data;
        image_desc.data.subimage[0][0].size = (size_t)(width * height * 4);

        Texture tex;

        tex.image = sg_make_image(image_desc);
        tex.height = height;
        tex.width = width;

        umap[name] = tex;

        stbi_image_free(data);

        return true;
    }

    void GraphicsManager::UpdateText(ecs::EntityID ent) {
        string editing = (ingengine::gameEngine.entity_manager.Get<Types::Text>(ent)).contents;

        switch (ingengine::gameEngine.input.GetKey()) {
        case GLFW_KEY_A:
            editing += "a"; break;
        case GLFW_KEY_B:
            editing += "b"; break;
        case GLFW_KEY_C:
            editing += "c"; break;
        case GLFW_KEY_D:
            editing += "d"; break;
        case GLFW_KEY_E:
            editing += "e"; break;
        case GLFW_KEY_F:
            editing += "f"; break;
        case GLFW_KEY_G:
            editing += "g"; break;
        case GLFW_KEY_H:
            editing += "h"; break;
        case GLFW_KEY_I:
            editing += "i"; break;
        case GLFW_KEY_J:
            editing += "j"; break;
        case GLFW_KEY_K:
            editing += "k"; break;
        case GLFW_KEY_L:
            editing += "l"; break;
        case GLFW_KEY_M:
            editing += "m"; break;
        case GLFW_KEY_N:
            editing += "n"; break;
        case GLFW_KEY_O:
            editing += "o"; break;
        case GLFW_KEY_P:
            editing += "p"; break;
        case GLFW_KEY_Q:
            editing += "q"; break;
        case GLFW_KEY_R:
            editing += "r"; break;
        case GLFW_KEY_S:
            editing += "s"; break;
        case GLFW_KEY_T:
            editing += "t"; break;
        case GLFW_KEY_U:
            editing += "u"; break;
        case GLFW_KEY_V:
            editing += "v"; break;
        case GLFW_KEY_W:
            editing += "w"; break;
        case GLFW_KEY_X:
            editing += "x"; break;
        case GLFW_KEY_Y:
            editing += "y"; break;
        case GLFW_KEY_Z:
            editing += "z"; break;
        case GLFW_KEY_BACKSPACE:
            editing = editing.substr(0, editing.length() - 1);
        case GLFW_KEY_ENTER:
            (ingengine::gameEngine.entity_manager.Get<Types::Text>(ent)).yPos += lh * 1.2f; break;
        }

        (ingengine::gameEngine.entity_manager.Get<Types::Text>(ent)).contents = editing;
    }
    /*
    void GraphicsManager::RenderText() {
        dpis = state.dpi_scale;

        sfetch_dowork();

        fonsClearState(state.fons);

        sgl_defaults();
        sgl_matrix_mode_projection();
        sgl_ortho(0.0f, sapp_widthf(), sapp_heightf(), 0.0f, -1.0f, +1.0f);

        FONScontext* fs = state.fons;
        if (state.font != FONS_INVALID) {
            fonsSetFont(fs, state.font);
            fonsSetSize(fs, 24.0f * dpis);
            fonsVertMetrics(fs, NULL, NULL, &lh);
            fonsSetColor(fs, white);
            ingengine::gameEngine.entity_manager.ForEach<Types::Text>([&](ecs::EntityID entity) {
                Types::Text& theText = ingengine::gameEngine.entity_manager.Get<Types::Text>(entity);
                fonsDrawText(fs, theText.xPos * dpis, theText.yPos * dpis, theText.contents.c_str(), NULL);
                });

            //dx = fonsDrawText(fs, dx, dy, message.c_str(), NULL);
        }

        sfons_flush(fs);

        //sg_pass_action sgPass{};

        pass_action.colors[0].action = SG_ACTION_CLEAR;
        pass_action.colors[0].value = { 0.3f, 0.3f, 0.32f, 1.0f };

        sg_begin_default_pass(pass_action, sapp_width(), sapp_height());
        sgl_draw();
        sg_end_pass();
        sg_commit();
    }*/

    void GraphicsManager::Draw(const std::vector< Sprite >& sprites) //const std::vector< Sprite >& sprites
    {
        int windowWidth, windowHeight;
        Uniforms uniforms;

        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        sg_begin_default_pass(pass_action, windowWidth, windowHeight);
        sg_apply_pipeline(pipeline);

        // Start with an identity matrix.
        uniforms.projection = glm::mat4{ 1 };

        // Scale x and y by 1/100.
        uniforms.projection[0][0] = uniforms.projection[1][1] = 1. / 100.;

        // Scale the long edge by an additional 1/(long/short) = short/long.
        if (windowWidth < windowHeight)
        {
            uniforms.projection[1][1] *= windowWidth;
            uniforms.projection[1][1] /= windowHeight;
        }
        else
        {
            uniforms.projection[0][0] *= windowWidth;
            uniforms.projection[0][0] /= windowHeight;
        }

        if (loaded == 0)
        {
            string path_string;

            for (const Sprite& sprite : sprites)
            {
                if (umap.find(sprite.image) == umap.end())
                {
                    path_string = ingengine::gameEngine.resources.ResolvePath("std_image", sprite.image).u8string();
                    // cout << path_string << endl;
                    LoadImage(sprite.image, path_string);
                }
            }

            cout << "LOADED ALL TEXTURES" << endl;
            loaded++;
        }

        for (const Sprite& sprite : sprites)
        {

            Texture tex = umap.at(sprite.image);

            //uniforms.transform = translate( glm::mat4{1}, glm::vec3( 0, 0, 0 ) ) * scale( glm::mat4{1}, glm::vec3( -100, -100, -100 ) );

            //                                                        x, y, z
            uniforms.transform = translate(glm::mat4{ 1 }, glm::vec3(sprite.x, sprite.y, sprite.z)) * scale(glm::mat4{ 1 }, glm::vec3(sprite.scale, -sprite.scale, -sprite.scale));

            if (tex.width < tex.height)
            {
                uniforms.transform = uniforms.transform * scale(glm::mat4{ 1 }, glm::vec3((float)tex.width / tex.height, 1.0, 1.0));
            }
            else
            {
                uniforms.transform = uniforms.transform * scale(glm::mat4{ 1 }, glm::vec3(1.0, (float)tex.height / tex.width, 1.0));
            }

            sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms));
            sg_apply_uniforms(SG_SHADERSTAGE_FS, 0, SG_RANGE(uniforms));
            bindings.fs_images[0] = tex.image;
            sg_apply_bindings(bindings);
            sg_draw(0, 4, 1);

        }

        sg_end_pass();
        sg_commit();
        glfwSwapBuffers(window);


    }

    void GraphicsManager::window_size_callback(GLFWwindow* window, int width, int height)
    {
        int w, h;
        //glfwGetWindowSize(window, &w, &h);
        //glfwSetWindowSize(window, w, h);
    }

    void cleanup(void) {
        __dbgui_shutdown();
        sfetch_shutdown();
        sfons_destroy(state.fons);
        sgl_shutdown();
        sg_shutdown();
    }

    sapp_desc sokol_main(int argc, char* argv[]) {
        (void)argc;
        (void)argv;
        sapp_desc sDesc{};
        sDesc.init_cb = init;
        sDesc.frame_cb = frame;
        sDesc.cleanup_cb = cleanup;
        sDesc.event_cb = __dbgui_event;
        sDesc.width = 800;
        sDesc.height = 600;
        sDesc.high_dpi = true;
        sDesc.gl_force_gles2 = true;
        sDesc.window_title = "fontstash";
        sDesc.icon.sokol_default = true;


        return sDesc;
    }
}