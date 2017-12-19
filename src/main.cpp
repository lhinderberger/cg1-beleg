#include <iostream>
#include <list>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Axises.h"
#include "Cylinder.h"
#include "InteractiveFirstPersonCamera.h"
#include "ShaderProgram.h"

using namespace cg1;
using namespace glm;
using namespace std;

typedef enum e_RenderMode { WIREFRAME = 0, SOLID = 1, TEXTURED = 2 } RenderMode;

GLuint mvpLocation;
int winWidth = 800, winHeight = 600;
int lastMouseX = -1, lastMouseY = -1;
mat4 projectionMatrix;
RenderMode renderMode = WIREFRAME;

InteractiveFirstPersonCamera camera;
list<unique_ptr<Model>> models;
unique_ptr<ShaderProgram> shaderProgram;

/* GLUT callbacks */
void keyboard(unsigned char key, int x, int y);
void passiveMouseMotion(int x, int y);
void render();
void reshape(int width, int height);
void specialKey(int key, int x, int y);

/* Other methods */
void generateModels();
void init(int argc, char ** args);
unique_ptr<ShaderProgram> loadShaders();
void setRenderMode(RenderMode mode);



int main(int argc, char ** args) {
    init(argc, args);
    generateModels();
    glutMainLoop();
    return 0;
}

void generateModels() {
    models.clear();
    models.emplace_back(new Axises());
    models.emplace_back(new Cylinder(0.25, 0.5, 16));
}

void init(int argc, char ** args) {
    // Initialize GLUT
    glutInit(&argc, args);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(4,0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Beleg Computergrafik 1 - Lucas Hinderberger (s75887)");
    //glutSetCursor(GLUT_CURSOR_NONE);

    // Print system information
    cout << "System information:" << endl << endl;

    cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL Version:" << glGetString(GL_VERSION) << endl;
    cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    cout << endl;

    // Initialize the GL Extension wrangler
    glewExperimental=GL_TRUE;
	if (glewInit())
        throw runtime_error("Error intitializing GLEW!");

    // Configure OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load shaders
    shaderProgram = loadShaders();
    shaderProgram->use();
    mvpLocation = glGetUniformLocation(shaderProgram->getId(), "mvp");

    // Set callbacks and run
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKey);
}

unique_ptr<ShaderProgram> loadShaders() {
    // Load the individual shaders
    FragmentShader fragment("shaders/fragment.fs");
    VertexShader vertex("shaders/vertex.vs");

    // Link shader program
    ShaderProgramFactory spFactory;
    spFactory.addShader(&fragment);
    spFactory.addShader(&vertex);
    unique_ptr<ShaderProgram> result = spFactory.link();

    return result;
}

void setRenderMode(RenderMode mode) {
    renderMode = mode;

    glPolygonMode(GL_FRONT_AND_BACK, (renderMode == WIREFRAME) ? GL_LINE : GL_FILL);
}


/* GLUT callbacks */
void keyboard(unsigned char key, int x, int y) {
    camera.processKey(key);
    if (key == 'q')
        exit(0);
    if (key == 'm')
        setRenderMode((RenderMode)((renderMode + 1) % 3));
    render();
}

void passiveMouseMotion(int x, int y) {
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

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    winWidth = width;
    winHeight = height;

    /* Recalculate aspect ratio and projection matrix */
    double aspectRatio = (double)width/height;
    //projectionMatrix = ortho(-1.0 * aspectRatio, aspectRatio, -1.0, 1.0, 0.01, 100.0);
    projectionMatrix = perspective(0.6, aspectRatio, 0.01, 100.0);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate view and projection matrices
    glm::mat4 viewMatrix = camera.getViewMatrix();

    for (const unique_ptr<Model> & model : models) {
        glm::mat4 mvp = projectionMatrix * viewMatrix * model->getModelMatrix();
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
        model->render();
    }

    glFlush();
}

void specialKey(int key, int x, int y) {
    camera.processSpecialKey(key);
    render();
}
