#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Application.h"

#include "Axises.h"
#include "Billboard.h"
#include "Dice.h"
#include "Plane.h"
#include "Overlay.h"

using namespace cg1;
using namespace glm;
using namespace std;

Application::Application() {
	initShaders();
	generateModels();
	
	// Configure OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0f);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Configure camera
    cameraOne.setPosition(vec3(0.0f,1.0f,5.0f));
    cameraTwo.setPosition(vec3(-3.0f,1.0f,-3.0f));
    cameraTwo.setYaw(radians(150.0f));
    currentCamera = &cameraOne;
}


void Application::idle() {
    int elapsedMs = glutGet(GLUT_ELAPSED_TIME);
    int elapsedSec = elapsedMs / 1000;
    if (elapsedSec > lastSecond) {
        billboard->step();
        lastSecond = elapsedSec;
    }
    diceRotation = (float)elapsedMs / 1000.0f;
    spinningDice->modelMatrix = rotate(translate(mat4(1.0f), vec3(1.0f,1.0f,2.0f)), diceRotation, vec3(0,1,0));
    spinningDice->modelMatrix = rotate(spinningDice->modelMatrix, diceRotation, vec3(0.5,0.5,0.5));
    glutPostRedisplay();
}

void Application::generateModels() {
	models.clear();
    //models.emplace_back(new Axises(this));
    
    overlay = new Overlay(this);
    
    Plane * ground = new Plane(this, 10.0f, 10.0f);
    ground->modelMatrix = translate(mat4(1.0f), vec3(-5.0f, 0.0f, -5.0f));
    models.emplace_back(ground);
    
    for (int i = 0; i < 10; i++) {
	    Dice * testDice = new Dice(this, 0.3f);
	    // This has the effect of pseudo-randomly scattering the dices around the scene
	    testDice->modelMatrix = rotate(mat4(1.0f), radians(80.0f) * i, vec3(0,1,0));
	    testDice->modelMatrix = translate(testDice->modelMatrix, vec3((float)i*0.4f,0,0.4f));
	    models.emplace_back(testDice);
    }
    
    spinningDice = new Dice(this, 0.3f);
    models.emplace_back(spinningDice);
    
    billboard = new Billboard(this);
    models.emplace_back(billboard);
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
    normalMatrixLocation = glGetUniformLocation(id, "normalMatrix");
    viewMatrixLocation = glGetUniformLocation(id, "viewMatrix");
    projectionMatrixLocation = glGetUniformLocation(id, "projectionMatrix");
    cameraPositionLocation = glGetUniformLocation(id, "cameraPosition");
    lightingEnabledLocation = glGetUniformLocation(id, "lightingEnabled");
    objectColorLocation = glGetUniformLocation(id, "objectColor");
    materialAmbientLocation = glGetUniformLocation(id, "material.ambient");
    materialDiffuseLocation = glGetUniformLocation(id, "material.diffuse");
    materialSpecularLocation = glGetUniformLocation(id, "material.specular");
    materialShininessLocation = glGetUniformLocation(id, "material.shininess");
    sunDirectionLocation = glGetUniformLocation(id, "sun.direction");
    sunAmbientLocation = glGetUniformLocation(id, "sun.ambient");
    sunDiffuseLocation = glGetUniformLocation(id, "sun.diffuse");
    sunSpecularLocation = glGetUniformLocation(id, "sun.specular");
    nPointLightsLocation = glGetUniformLocation(id, "nPointLights");
    texturingEnabledLocation = glGetUniformLocation(id, "texturingEnabled");
}

void Application::setLightingEnabled(bool lightingEnabled) {
	this->lightingEnabled = lightingEnabled;
	glUniform1i(lightingEnabledLocation, lightingEnabled ? GL_TRUE : GL_FALSE);
}

void Application::setMaterial(const Material & material) {
    glUniform3fv(materialAmbientLocation, 1, (const GLfloat*)&(material.ambient));
    glUniform3fv(materialDiffuseLocation, 1, (const GLfloat*)&(material.diffuse));
    glUniform3fv(materialSpecularLocation, 1, (const GLfloat*)&(material.specular));
    glUniform1f(materialShininessLocation, material.shininess);
}

void Application::setObjectColor(const vec4 & color) {
    glUniform4fv(objectColorLocation, 1, (const float*)&color);
}

void Application::setRenderMode(RenderMode mode) {
    renderMode = mode;
    glPolygonMode(GL_FRONT_AND_BACK, (renderMode == WIREFRAME) ? GL_LINE : GL_FILL);
    setTexturingEnabled(texturingEnabled);
    glutPostRedisplay();
}

void Application::setTexturingEnabled(bool texturingEnabled) {
	this->texturingEnabled = texturingEnabled;
	glUniform1i(texturingEnabledLocation, texturingEnabled && renderMode == TEXTURED ? GL_TRUE : GL_FALSE);
}




void Application::keyboard(unsigned char key, int x, int y) {
    currentCamera->processKey(key);
    if (key == 'q')
        exit(0);
    else if (key == 'm')
        setRenderMode((RenderMode)((renderMode + 1) % 3));
    else if (key == 'b')
        billboard->cyclePattern();
    else if (key == 'o')
        displayOverlay = !displayOverlay;
    else if (key == '1') {
        currentCamera = &cameraOne;
        orthogonalMode = false;
    }
    else if (key == '2') {
        currentCamera = &cameraOne;
        orthogonalMode = true;
    }
    else if (key == '3') {
        currentCamera = &cameraTwo;
        orthogonalMode = false;
    }
    else if (key == '4') {
        currentCamera = &cameraTwo;
        orthogonalMode = true;
    }
    
    glutPostRedisplay();
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
        currentCamera->processRelativeMouseMotion(winRelativeX, winRelativeY);

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
    glutPostRedisplay();
}

void Application::reshape(int width, int height) {
    winWidth = width;
    winHeight = height;
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, winWidth * 0.75, winHeight);
    renderImpl(currentCamera, displayOverlay, orthogonalMode);
    
    
    glViewport(winWidth * 0.75, winHeight * 0.75, winWidth * 0.25, winHeight * 0.25);
    renderImpl(&cameraOne, false, false);
    
    glViewport(winWidth * 0.75, winHeight * 0.5, winWidth * 0.25, winHeight * 0.25);
    renderImpl(&cameraOne, false, true);
    
    glViewport(winWidth * 0.75, winHeight * 0.25, winWidth * 0.25, winHeight * 0.25);
    renderImpl(&cameraTwo, false, false);
    
    glViewport(winWidth * 0.75, 0, winWidth * 0.25, winHeight * 0.25);
    renderImpl(&cameraTwo, false, true);
    
    glFlush();
}

void Application::renderImpl(FirstPersonCamera * camera, bool renderOverlay, bool orthogonalMode) {
    // Calculate view and projection matrices
    glm::mat4 viewMatrix = camera->getViewMatrix();
    
    double aspectRatio = (double)winWidth*0.7/winHeight;
    if (orthogonalMode)
        projectionMatrix = ortho(-1.0 * aspectRatio, aspectRatio, -1.0, 1.0, 0.01, 100.0);
    else
        projectionMatrix = perspective(0.6, aspectRatio, 0.01, 100.0);
    
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    
    // Setup uniforms
    glUniform3fv(cameraPositionLocation, 1, (const float*)&currentCamera->getPosition());
	setLightingEnabled(true);
	
	// Setup lights
    setupSunLight();
    setupPointLights();
	
	// Render each model
	for (const unique_ptr<Model> & model : models)
        model->render();
    
    // Render overlay
    if (renderOverlay) {
        glDisable(GL_DEPTH_TEST);
        setLightingEnabled(false);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &mat4(1.0f)[0][0]);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &mat4(1.0f)[0][0]);
        overlay->render();
        glEnable(GL_DEPTH_TEST);
    }
}

void Application::setupPointLights() {
    list<PointLight> pointLights;
    
    // Retrieve all point lights in the scene
    for (const unique_ptr<Model> & model : models)
        pointLights.splice(pointLights.end(), model->getPointLights());
        
    // Set uniforms
    GLuint id = shaderProgram->getId();
    int i = 0;
    for (const PointLight & l : pointLights) {
        if (i > MAX_POINT_LIGHTS) {
            cerr << "Max Point Lights exceeded!" << endl;
            i--;
            break;
        }
        
        char prefix[64];
        sprintf(prefix, "pointLights[%d].", i);
        string sPrefix(prefix);
        
        glUniform3fv(glGetUniformLocation(id, (sPrefix + "position").c_str()), 1, (const float*)&l.position);
        glUniform3fv(glGetUniformLocation(id, (sPrefix + "ambient").c_str()), 1, (const float*)&l.ambient);
        glUniform3fv(glGetUniformLocation(id, (sPrefix + "diffuse").c_str()), 1, (const float*)&l.diffuse);
        glUniform3fv(glGetUniformLocation(id, (sPrefix + "specular").c_str()), 1, (const float*)&l.specular);
        glUniform1f(glGetUniformLocation(id, (sPrefix + "constantDecay").c_str()), l.constantDecay);
        glUniform1f(glGetUniformLocation(id, (sPrefix + "linearDecay").c_str()), l.linearDecay);
        glUniform1f(glGetUniformLocation(id, (sPrefix + "quadraticDecay").c_str()), l.quadraticDecay);

        i++;
    }
    
    glUniform1i(nPointLightsLocation, i);
    
}

void Application::setupSunLight() {
    glUniform3fv(sunDirectionLocation, 1, (const float*)&sun.direction);
    glUniform3fv(sunAmbientLocation, 1, (const float*)&sun.ambient);
    glUniform3fv(sunDiffuseLocation, 1, (const float*)&sun.diffuse);
    glUniform3fv(sunSpecularLocation, 1, (const float*)&sun.specular);
}

void Application::specialKey(int key, int x, int y) {
    currentCamera->processSpecialKey(key);
    glutPostRedisplay();
}

