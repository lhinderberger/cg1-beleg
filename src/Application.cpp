#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Application.h"

#include "Axises.h"
#include "Billboard.h"

using namespace cg1;
using namespace glm;
using namespace std;

Application::Application() {
	initShaders();
	generateModels();
	
	// Configure OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Configure camera
    camera.setPosition(vec3(0.0f,1.0f,5.0f));
}


void Application::generateModels() {
	models.clear();
    models.emplace_back(new Axises(this));
    
    Billboard * b = new Billboard(this);
    models.emplace_back(b);
    
    for (int i = 0; i < 10; i++) {
	    Cuboid * testBox = new Cuboid(this, 0.3f,0.3f,0.3f);
	    testBox->modelMatrix = translate(mat4(1.0f), vec3((float)i*0.4f,0,0.4f));
	    models.emplace_back(testBox);
    }
}

void Application::initShaders() {
    // Load the individual shaders
    FragmentShader fragment("shaders/fragment.fs");
    VertexShader vertex("shaders/vertex.vs");

    // Link shader program
    ShaderProgramFactory spFactory;
    spFactory.addShader(&fragment);
    spFactory.addShader(&vertex);
    shaderProgram = spFactory.link();
    
    // Retrieve uniform locations
    shaderProgram->use();
    GLuint id = shaderProgram->getId();
    modelMatrixLocation = glGetUniformLocation(id, "modelMatrix");
    viewMatrixLocation = glGetUniformLocation(id, "viewMatrix");
    projectionMatrixLocation = glGetUniformLocation(id, "projectionMatrix");
    lightingEnabledLocation = glGetUniformLocation(id, "lightingEnabled");
    objectColorLocation = glGetUniformLocation(id, "objectColor");
}

void Application::setLightingEnabled(bool lightingEnabled) {
	this->lightingEnabled = lightingEnabled;
	glUniform1i(lightingEnabledLocation, lightingEnabled ? GL_TRUE : GL_FALSE);
}

void Application::setObjectColor(const vec4 & color) {
    glUniform4fv(objectColorLocation, 1, (const float*)&color);
}

void Application::setRenderMode(RenderMode mode) {
    renderMode = mode;
    glPolygonMode(GL_FRONT_AND_BACK, (renderMode == WIREFRAME) ? GL_LINE : GL_FILL);
    render();
}




void Application::keyboard(unsigned char key, int x, int y) {
    camera.processKey(key);
    if (key == 'q')
        exit(0);
    if (key == 'm')
        setRenderMode((RenderMode)((renderMode + 1) % 3));
    render();
}

void Application::passiveMouseMotion(int x, int y) {
    /* Calculate relative movement */
    int relativeX = x - lastMouseX;
    int relativeY = y - lastMouseY;
    float winRelativeX = (float)relativeX / (float)winWidth;
    float winRelativeY = (float)relativeY / (float)winHeight;

    /* Ignore first movement, ignore large movements (we assume they're warps) */
    if (lastMouseX != -1 && abs(relativeX) <= 100 && abs(relativeY) <= 100) {
        /* Adjust camera direction */
        camera.processRelativeMouseMotion(winRelativeX, winRelativeY);

        /* Warp mouse to the opposite edge of window, if at edge */
        int newX = x;
        int newY = y;
        if (x < 10) newX = winWidth - 20;
        if (x > (winWidth - 10)) newX = 20;
        if (y < 10) newY = winHeight - 20;
        if (y > (winHeight - 10)) newY = 20;

        if (newX != x || newY != y)
            glutWarpPointer(newX, newY);
    }

    lastMouseX = x;
    lastMouseY = y;
    render();
}

void Application::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    winWidth = width;
    winHeight = height;

    /* Recalculate aspect ratio and projection matrix */
    double aspectRatio = (double)width/height;
    //projectionMatrix = ortho(-1.0 * aspectRatio, aspectRatio, -1.0, 1.0, 0.01, 100.0);
    projectionMatrix = perspective(0.6, aspectRatio, 0.01, 100.0);
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate view and projection matrices
    glm::mat4 viewMatrix = camera.getViewMatrix();
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	setLightingEnabled(true);
	vec3 ambient = vec3(0.1f,0.1f,0.1f);
	glUniform3fv(glGetUniformLocation(shaderProgram->getId(), "lightColor"),1,(float*)&ambient);
    for (const unique_ptr<Model> & model : models)
        model->render();

    glFlush();
}

void Application::specialKey(int key, int x, int y) {
    camera.processSpecialKey(key);
    render();
}

