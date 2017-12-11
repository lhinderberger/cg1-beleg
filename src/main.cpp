#include <iostream>
#include <list>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Axises.h"
#include "ShaderProgram.h"

using namespace cg1;
using namespace glm;
using namespace std;

GLuint mvpLocation;
int winWidth = 800, winHeight = 600;
mat4 projectionMatrix, viewMatrix;
list<unique_ptr<Renderable>> renderables;
unique_ptr<ShaderProgram> shaderProgram;

/* GLUT callbacks */
void keyboard(unsigned char key, int x, int y);
void render();
void reshape(int width, int height);

/* Other methods */
void generateRenderables();
void init(int argc, char ** args);
unique_ptr<ShaderProgram> loadShaders();



int main(int argc, char ** args) {
    init(argc, args);
    generateRenderables();    
    glutMainLoop();
    return 0;
}

void generateRenderables() {
    renderables.clear();
    renderables.emplace_back(new Axises());
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
    glutReshapeFunc(reshape);
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


/* GLUT callbacks */
void keyboard(unsigned char key, int x, int y) {
    if (key == 'q')
        exit(0);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    winWidth = width;
    winHeight = height;

    /* Recalculate aspect ratio and projection matrix */
    double aspectRatio = (double)width/height;
    projectionMatrix = ortho(-1.0 * aspectRatio, aspectRatio, -1.0, 1.0, 0.01, 100.0);
    //projectionMatrix = perspective(0.6, aspectRatio, 0.01, 100.0);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate view and projection matrices
    glm::mat4 viewMatrix = lookAt(vec3(2,2,2), vec3(0,0,0), vec3(0,1,0));
    glm::mat4 pv = projectionMatrix * viewMatrix;
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &pv[0][0]);
    
    for (const unique_ptr<Renderable> & renderable : renderables)
        renderable->render();

    glFlush();
}
