#include <GL/glew.h>
#include "Cuboid.h"

#include <vector>

using namespace cg1;
using namespace glm;
using namespace std;

Cuboid::Cuboid(Application * application, float width, float height, float depth)
	: Model(application) {
    float vertices[] = {
    	// Position				// Normal
        0,0,0,                  0,0,-1,
        width,0,0,              0,0,-1,
        0,height,0,             0,0,-1,
        
        0,height,0,             0,0,-1,
        width,height,0,         0,0,-1,
        width,0,0,              0,0,-1,
        
        
        0,0,depth,              0,0,1,
        width,0,depth,          0,0,1,
        0,height,depth,         0,0,1,
        
        0,height,depth,         0,0,1,
        width,height,depth,     0,0,1,
        width,0,depth,          0,0,1,
        
        
        0,0,0,                  -1,0,0,
        0,0,depth,              -1,0,0,
        0,height,0,             -1,0,0,
        
        0,height,0,             -1,0,0,
        0,0,depth,              -1,0,0,
        0,height,depth,         -1,0,0,
        
        
        width,0,0,              1,0,0,
        width,0,depth,          1,0,0,
        width,height,0,         1,0,0,
        
        width,height,0,         1,0,0,
        width,0,depth,          1,0,0,
        width,height,depth,     1,0,0,
        
        
        0,0,0,                  0,-1,0,
        0,0,depth,              0,-1,0,
        width,0,0,              0,-1,0,
        
        width,0,0,              0,-1,0,
        0,0,depth,              0,-1,0,
        width,0,depth,          0,-1,0,
        
        
        0,height,0,             0,1,0,
        0,height,depth,         0,1,0,
        width,height,0,         0,1,0,
        
        width,height,0,         0,1,0,
        0,height,depth,         0,1,0,
        width,height,depth,     0,1,0
    };
    
    vao = VAO::create(vertices, 36*6);
    vao->setupAttribPointer(0,3,6);
    vao->setupAttribPointer(1,3,6,3);
}

void Cuboid::render(glm::mat4 parentModelMatrix) {
    vao->bind();
    setModelAndNormalMatrixUniform(parentModelMatrix * modelMatrix);
    
    getApplication()->setObjectColor(getColor());
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
