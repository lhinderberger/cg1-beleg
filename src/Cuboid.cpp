#include <GL/glew.h>
#include "Cuboid.h"

#include <vector>

using namespace cg1;
using namespace glm;
using namespace std;

Cuboid::Cuboid(float width, float height, float depth) {
    float vertices[] = {
        0,0,0, width,0,0, 0,height,0,
        0,height,0, width,height,0, width,0,0,
        
        0,0,depth, width,0,depth, 0,height,depth,
        0,height,depth, width,height,depth, width,0,depth,
        
        0,0,0, 0,0,depth, 0,height,0,
        0,height,0, 0,0,depth, 0,height,depth,
        
        width,0,0, width,0,depth, width,height,0,
        width,height,0, width,0,depth, width,height,depth,
        
        0,0,0, 0,0,depth, width,0,0,
        width,0,0, 0,0,depth, width,0,depth,
        
        0,height,0, 0,height,depth, width,height,0,
        width,height,0, 0,height,depth, width,height,depth
    };
    
    vao = VAO::create(vertices, 36, 3);
}

void Cuboid::render() {
    vao->bind();
    
    const vec4 & color = getColor();
    glVertexAttrib4f(1, color.r, color.g, color.b, color.a);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
