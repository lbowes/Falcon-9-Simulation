#include "Mesh.h"
#include "../3rd_party/imgui/imgui.h"
#include "CameraSystem.h"
#include "ShaderUtils.h"

#include <bgfx/platform.h>
#include <bx/math.h>


namespace F9Sim {
namespace Graphics {


bgfx::VertexLayout Vertex::ms_layout;


uint64_t Mesh::s_renderState =
    0 |
    BGFX_STATE_WRITE_RGB |
    BGFX_STATE_WRITE_A |
    BGFX_STATE_WRITE_Z |
    BGFX_STATE_DEPTH_TEST_LESS |
    BGFX_STATE_MSAA |
    BGFX_STATE_MSAA;


Mesh::Mesh(const char* filepath) {

    Vertex::init();

    // Get the data from the obj file into the correct bgfx objects ready for rendering
    // (this is just temporary data for testing camera movement)
    {
        static Vertex s_cubeVertices[] = {
            {-1.0f, 1.0f, 1.0f, 0xff00ffff},
            {1.0f, 1.0f, 1.0f, 0xffffffff},
            {-1.0f, -1.0f, 1.0f, 0xff0000ff},
            {1.0f, -1.0f, 1.0f, 0xffff0000},
            {-1.0f, 1.0f, -1.0f, 0xff00ff00},
            {1.0f, 1.0f, -1.0f, 0xffffff00},
            {-1.0f, -1.0f, -1.0f, 0xff000000},
            {1.0f, -1.0f, -1.0f, 0xffff0000},
        };

        m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)), Vertex::ms_layout);

        static const uint16_t s_cubeTriList[] = {
            0,
            1,
            2, // 0
            1,
            3,
            2,
            4,
            6,
            5, // 2
            5,
            6,
            7,
            0,
            2,
            4, // 4
            4,
            2,
            6,
            1,
            5,
            3, // 6
            5,
            7,
            3,
            0,
            4,
            1, // 8
            4,
            5,
            1,
            2,
            3,
            6, // 10
            6,
            3,
            7,
        };

        m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList)));
    }

    // Set up shader
    bgfx::ShaderHandle vsh = loadShader("resources/shaders/v_square.bin");
    bgfx::ShaderHandle fsh = loadShader("resources/shaders/f_square.bin");
    m_shader = bgfx::createProgram(vsh, fsh, true);
}


Mesh::~Mesh() {
    bgfx::destroy(m_vbh);
    bgfx::destroy(m_ibh);
    bgfx::destroy(m_shader);
}


void Mesh::setTransform(Transform newTransform) {
    m_transform = newTransform;
}


void Mesh::draw(glm::dvec3 camPos) const {
    updateTransformRelativeTo(camPos);

    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);
    bgfx::setState(s_renderState);
    bgfx::submit(0, m_shader);
}


void Mesh::updateTransformRelativeTo(glm::dvec3 camPos) const {
    // Rotation
    const bx::Quaternion orientation = {
        (float)m_transform.orientation.w,
        (float)m_transform.orientation.x,
        (float)m_transform.orientation.y,
        (float)m_transform.orientation.z};

    float rotation[16];
    bx::mtxQuat(rotation, orientation);

    // Translation
    const glm::dvec3 d = m_transform.position - camPos;
    float translation[16];
    bx::mtxTranslate(translation, (float)d.x, (float)d.y, (float)d.z);

    // Combine rotation and translation
    float transform[16];
    bx::mtxMul(transform, rotation, translation);
    bgfx::setTransform(transform);
}


} // namespace Graphics
} // namespace F9Sim
