#include <GL/glew.h>
#include "Axises.h"

using namespace std;
using namespace cg1;
using namespace glm;

Axises::Axises(Application * application, float length) : Model(application) {
    const int nVertices = 18;
    float vertices[nVertices] = {
        length * -0.5f, 0.0f, 0.0f,
        length * 0.5f, 0.0f, 0.0f,
        
        0.0f, length * -0.5f, 0.0f,
        0.0f, length * 0.5f, 0.0f,
        
        0.0f, 0.0f, length * -0.5f,
        0.0f, 0.0f, length * 0.5f
    };
    vao = VAO::create(vertices, nVertices);
    vao->setupAttribPointer(0, 3);
}


void Axises::render(glm::mat4 parentModelMatrix) {
	Application * application = getApplication();
	
	bool lightingEnabled = application->getLightingEnabled();
	application->setLightingEnabled(false);
	
    setModelMatrixUniform(parentModelMatrix * modelMatrix);
    
    vao->bind();
    
    glVertexAttrib4f(1, 1.0f, 0.0f, 0.0f, 0.5f);
    glDrawArrays(GL_LINES, 0, 2);
    
    glVertexAttrib4f(1, 0.0f, 1.0f, 0.0f, 0.5f);
    glDrawArrays(GL_LINES, 2, 2);
    
    glVertexAttrib4f(1, 0.0f, 0.0f, 1.0f, 0.5f);
    glDrawArrays(GL_LINES, 4, 2);
    application->setLightingEnabled(lightingEnabled);
}
