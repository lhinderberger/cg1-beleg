#include <GL/glew.h>
#include "Axises.h"

using namespace std;
using namespace cg1;
using namespace glm;

Axises::Axises(Application * application, float length) : Model(application) {
    vao = VAO::create(vector<vec3> {
        vec3(length * -0.5f, 0.0f, 0.0f), vec3(length * 0.5f, 0.0f, 0.0f),
        vec3(0.0f, length * -0.5f, 0.0f), vec3(0.0f, length * 0.5f, 0.0f),
        vec3(0.0f, 0.0f, length * -0.5f), vec3(0.0f, 0.0f, length * 0.5f)
    });
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
