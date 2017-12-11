#include <GL/glew.h>
#include "Axises.h"

using namespace std;
using namespace cg1;
using namespace glm;

Axises::Axises(float length) {
    vao = VAO::create(vector<vec3> {
        vec3(length * -0.5f, 0.0f, 0.0f), vec3(length * 0.5f, 0.0f, 0.0f),
        vec3(0.0f, length * -0.5f, 0.0f), vec3(0.0f, length * 0.5f, 0.0f),
        vec3(0.0f, 0.0f, length * -0.5f), vec3(0.0f, 0.0f, length * 0.5f)
    });
}


void Axises::render() {
    vao->bind();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glVertexAttrib4f(1, 1.0f, 0.0f, 0.0f, 0.5f);
    glDrawArrays(GL_LINES, 0, 2);
    
    glVertexAttrib4f(1, 0.0f, 1.0f, 0.0f, 0.5f);
    glDrawArrays(GL_LINES, 2, 2);
    
    glVertexAttrib4f(1, 0.0f, 0.0f, 1.0f, 0.5f);
    glDrawArrays(GL_LINES, 4, 2);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
