#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <FreeImage.h>

#include "Application.h"

using namespace cg1;
using namespace glm;
using namespace std;

Application * application = nullptr;

/* GLUT callbacks */
void keyboard(unsigned char key, int x, int y);
void passiveMouseMotion(int x, int y);
void render();
void reshape(int width, int height);
void specialKey(int key, int x, int y);
void idle();

/* Other methods */
void init(int argc, char ** args);

int main(int argc, char ** args) {
    FreeImage_Initialise();
    
	try {
	    init(argc, args);
    	glutMainLoop();
    	if (application)
    		delete application;
    	return 0;
	}
	catch(exception & e) {
		cerr << "Exception caught: " << e.what() << endl;
		return 1;
	}
	
	FreeImage_DeInitialise();
}

void init(int argc, char ** args) {
    // Initialize GLUT
    glutInit(&argc, args);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion(4,0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitWindowSize(800, 600);
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
    
    // Create application
    application = new Application();

    // Setup callbacks
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKey);
    glutIdleFunc(idle);
}


/* GLUT callbacks */
void keyboard(unsigned char key, int x, int y) {
    if (application)
    	application->keyboard(key,x,y);
}

void passiveMouseMotion(int x, int y) {
    if (application)
    	application->passiveMouseMotion(x,y);
}

void reshape(int width, int height) {
    if (application)
    	application->reshape(width, height);
}

void render() {
    if (application)
    	application->render();
    glutSwapBuffers();
}

void specialKey(int key, int x, int y) {
    if (application)
    	application->specialKey(key,x,y);
}

void idle() {
    if (application)
        application->idle();  
}
