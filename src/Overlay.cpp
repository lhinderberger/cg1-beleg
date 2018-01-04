#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Overlay.h"

#include <vector>
#include "Texture.h"

using namespace cg1;
using namespace glm;
using namespace std;

static Texture * texture = nullptr;

Overlay::Overlay(Application * application)
	: Model(application) {
	float width = 2.0f;
	float height = 2.0f;
    float vertices[] = {
    	// Position			    // Normal   // Texture Coordinates
        0,0,0,                  0,0,1,     0,0,
        width,0,0,              0,0,1,     1,0,
        0,height,0,             0,0,1,     0,1,
        
        0,height,0,             0,0,1,     0,1,
        width,height,0,         0,0,1,     1,1,
        width,0,0,              0,0,1,     1,0
    };
    
    modelMatrix = translate(mat4(1.0f), vec3(-1.0f,-1.0f,0.0f));
    
    vao = VAO::create(vertices, 6*8);
    vao->setupAttribPointer(0,3,8);
    vao->setupAttribPointer(1,3,8,3);
    vao->setupAttribPointer(2,2,8,6);
    
    if (!texture)
        texture = new Texture("overlay.png");
}

void Overlay::render(glm::mat4 parentModelMatrix) {
    getApplication()->setTexturingEnabled(true);
    texture->bind();
    
    vao->bind();
    setModelAndNormalMatrixUniform(parentModelMatrix * modelMatrix);
    
    getApplication()->setMaterial(material);
    getApplication()->setObjectColor(getColor());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    getApplication()->setTexturingEnabled(false);
}
