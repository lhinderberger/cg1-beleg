#include <GL/glew.h>
#include "Hemisphere.h"

using namespace cg1;
using namespace glm;

Hemisphere::Hemisphere(float radius) {
    float vertices[] = {
        -radius,0,radius,
        radius,0,radius,
        0,radius,0,

        -radius,0,radius,
        -radius,0,-radius,
        0,radius,0,

        radius,0,radius,
        radius,0,-radius,
        0,radius,0,

        -radius,0,-radius,
        radius,0,-radius,
        0,radius,0
    };

    vao = VAO::create(vertices, 12, 3);
}

void Hemisphere::render() {
    vao->bind();

    const vec4 & color = getColor();
    glVertexAttrib4f(1, color.r, color.g, color.b, color.a);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
