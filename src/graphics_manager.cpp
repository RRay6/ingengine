#include "graphics_manager.h"
#include <iostream>
#include <string>

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"

#include "resource_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/vec3.hpp>
#include "glm/gtx/transform.hpp"

#include "uniforms.h"

using namespace std;


namespace graphics_manager {

    GLFWwindow* window;
    resource_manager::ResourceManager resources;
    sg_image image;
    int width, height, channels;
    sg_pipeline pipeline;
    sg_pass_action pass_action{};
    sg_bindings bindings{};
    sg_shader_desc shader_desc{};

void GraphicsManager::Startup()
{

    int window_width = 500;
    int window_height = 500;
    // std::string window_name = "ingengine";
    bool window_fullscreen = false;

    glfwInit();
    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    window = glfwCreateWindow( window_width, window_height, "ingengine", window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0 );
    glfwSetWindowAspectRatio( window, window_width, window_height );
    
    if( !window )
    {
        std::cerr << "Failed to create a window." << std::endl;
        //std::cout << "Failed to create a window.\n";
        glfwTerminate();
    }
    // else
    // {
    //     std::cerr << "It's good." << std::endl;
    // }

    glfwMakeContextCurrent( window );
    glfwSwapInterval(1);
    //glfwPollEvents();

    glfwSetWindowCloseCallback(window, WindowClosed);

    
        sg_desc desc{};
        sg_setup(&desc);
    

    
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
        pipeline_desc.shader = sg_make_shader( shader_desc );
        pipeline = sg_make_pipeline( pipeline_desc );

        pass_action.colors[0].action = SG_ACTION_CLEAR;
        pass_action.colors[0].value = {  }; // SG_DEFAULT_CLEAR_RED, SG_DEFAULT_CLEAR_GREEN, SG_DEFAULT_CLEAR_BLUE, SG_DEFAULT_CLEAR_ALPHA
        //Magum::Math::Color4::from(pass_action.colors[0].value) = 0x1f1f1f_rgbf;

        bindings.vertex_buffers[0] = vertex_buffer;
        //bindings.fs_images[0] = image;

        Draw();
        
    
    //glfwTerminate();
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

bool GraphicsManager::LoadImage( const string& name, const string& path ) //const string& name, const string& path
{
    //std::string path_string{resources.ResolvePath("sounds", "click.wav").u8string()};

    unsigned char* data = stbi_load( path.c_str(), &width, &height, &channels, 4 );

    if (data == 0) {
        cout << "Error loading image file" << endl;
    }
    else
    {
        cout << "It worked :D" << endl;
    }

    //{
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

        image = sg_make_image( image_desc );
        stbi_image_free( data );
    //}

    return false;
}

void GraphicsManager::Draw() //const std::vector< Sprite >& sprites
{
    int windowWidth, windowHeight;
    Uniforms uniforms;

    string path_string{resources.ResolvePath("std_image", "lulu_the_cat.jpg").u8string()};
    cout << path_string << endl;
    LoadImage("lulu_the_cat.jpg", path_string);

	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    sg_begin_default_pass( pass_action, windowWidth, windowHeight );
    sg_apply_pipeline( pipeline );

    // Start with an identity matrix.
    uniforms.projection = glm::mat4{1};
    // Scale x and y by 1/100.
    uniforms.projection[0][0] = uniforms.projection[1][1] = 1./100.;
    // Scale the long edge by an additional 1/(long/short) = short/long.
    if( windowWidth < windowHeight ) 
    {
        uniforms.projection[1][1] *= windowWidth;
        uniforms.projection[1][1] /= windowHeight;
    }
    else 
    {
        uniforms.projection[0][0] *= windowWidth;
        uniforms.projection[0][0] /= windowHeight;
    }

    uniforms.transform = translate( glm::mat4{1}, glm::vec3( 2, 2, 1 ) ) * scale( glm::mat4{1}, glm::vec3( -100, -100, -100 ) );

    if( width < height ) 
    {
        uniforms.transform = uniforms.transform * scale( glm::mat4{1}, glm::vec3((float)width/height, 1.0, 1.0 ) );
    } 
    else 
    {
        uniforms.transform = uniforms.transform * scale( glm::mat4{1}, glm::vec3( 1.0, (float)height/width, 1.0 ) );
    }

    sg_apply_uniforms( SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms) );
    bindings.fs_images[0] = image;
    sg_apply_bindings(bindings);
    sg_draw(0, 4, 1);
    sg_end_pass();
    sg_commit();
    glfwSwapBuffers(window);

}

}