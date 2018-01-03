#include <GL/glew.h>
#include "Cuboid.h"

#include <vector>

using namespace cg1;
using namespace glm;
using namespace std;

Cuboid::Cuboid(Application * application, float width, float height, float depth)
	: Model(application) {
	float s = 1.0f/6.0f;
    float vertices[] = {
    	// Position				// Normal   // Texture Coordinates
        0,0,0,                  0,0,-1,     0,0,
        width,0,0,              0,0,-1,     0,1,
        0,height,0,             0,0,-1,     s,0,
        
        0,height,0,             0,0,-1,     s,0,
        width,height,0,         0,0,-1,     s,1,
        width,0,0,              0,0,-1,     0,1,
        
        
        0,0,depth,              0,0,1,      2*s,0,
        width,0,depth,          0,0,1,      2*s,1,
        0,height,depth,         0,0,1,      s,0,
        
        0,height,depth,         0,0,1,      s,0,
        width,height,depth,     0,0,1,      s,1,
        width,0,depth,          0,0,1,      2*s,1,
        
        
        0,0,0,                  -1,0,0,     2*s,0,
        0,0,depth,              -1,0,0,     3*s,0,
        0,height,0,             -1,0,0,     2*s,1,
        
        0,height,0,             -1,0,0,     2*s,1,
        0,0,depth,              -1,0,0,     3*s,0,
        0,height,depth,         -1,0,0,     3*s,1,
        
        
        width,0,0,              1,0,0,      4*s,0,
        width,0,depth,          1,0,0,      3*s,0,
        width,height,0,         1,0,0,      4*s,1,
        
        width,height,0,         1,0,0,      4*s,1,
        width,0,depth,          1,0,0,      3*s,0,
        width,height,depth,     1,0,0,      3*s,1,
        
        
        0,0,0,                  0,-1,0,     4*s,0,
        0,0,depth,              0,-1,0,     4*s,1,
        width,0,0,              0,-1,0,     5*s,0,
        
        width,0,0,              0,-1,0,     5*s,0,
        0,0,depth,              0,-1,0,     4*s,1,
        width,0,depth,          0,-1,0,     5*s,1,
        
        
        0,height,0,             0,1,0,      5*s,1,
        0,height,depth,         0,1,0,      5*s,0,
        width,height,0,         0,1,0,      6*s,1,
        
        width,height,0,         0,1,0,      6*s,1,
        0,height,depth,         0,1,0,      5*s,0,
        width,height,depth,     0,1,0,      6*s,0
    };
    
    vao = VAO::create(vertices, 36*8);
    vao->setupAttribPointer(0,3,8);
    vao->setupAttribPointer(1,3,8,3);
    vao->setupAttribPointer(2,2,8,6);
}

void Cuboid::render(glm::mat4 parentModelMatrix) {
    vao->bind();
    setModelAndNormalMatrixUniform(parentModelMatrix * modelMatrix);
    
    getApplication()->setMaterial(material);
    getApplication()->setObjectColor(getColor());
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
