#ifndef CG1_APPLICATION_H
#define CG1_APPLICATION_H

#include <list>
#include <memory>

#include <GL/gl.h>
#include <glm/glm.hpp>

#include "InteractiveFirstPersonCamera.h"
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "ShaderProgram.h"

#define MAX_POINT_LIGHTS 100 // If needed, change in fragment shader as well

namespace cg1 {
    class Billboard;
    class Dice;
	typedef enum e_RenderMode { WIREFRAME = 0, SOLID = 1, TEXTURED = 2 } RenderMode;
	
	class Application {
	private:
	    int lastSecond = 0;
    	float diceRotation = 0.0f;
    	Billboard * billboard;
        Dice * spinningDice;
	
		bool lightingEnabled = false;
		bool texturingEnabled = false;
		int winWidth = 800, winHeight = 600;
		int lastMouseX = -1, lastMouseY = -1;

		RenderMode renderMode = TEXTURED;
		
		InteractiveFirstPersonCamera camera;
		
		std::list<std::unique_ptr<Model>> models;
		
		std::unique_ptr<ShaderProgram> shaderProgram;
		glm::mat4 projectionMatrix;
		DirectionalLight sun;
		GLuint modelMatrixLocation, normalMatrixLocation, viewMatrixLocation,
		projectionMatrixLocation, objectColorLocation, lightingEnabledLocation,
		cameraPositionLocation, materialAmbientLocation, materialDiffuseLocation,
		materialSpecularLocation, materialShininessLocation, sunDirectionLocation,
		sunAmbientLocation, sunDiffuseLocation, sunSpecularLocation, nPointLightsLocation,
		texturingEnabledLocation;
		
		void generateModels();
		void initShaders();
		void setupSunLight();
		void setupPointLights();
		
	public:
		Application();
		
		inline bool getLightingEnabled() const { return lightingEnabled; }
		inline GLuint getModelMatrixLocation() const { return modelMatrixLocation; }
		inline GLuint getNormalMatrixLocation() const { return normalMatrixLocation; }
		inline GLuint getViewMatrixLocation() const { return viewMatrixLocation; }
		inline GLuint getProjectionMatrixLocation() const { return projectionMatrixLocation; }
		
		void setLightingEnabled(bool lightingEnabled);
		void setTexturingEnabled(bool texturingEnabled);
		void setMaterial(const Material & material);
		void setObjectColor(const glm::vec4 & color);
		void setRenderMode(RenderMode mode);
		
		/* GLUT callbacks */
		void idle();
		void keyboard(unsigned char key, int x, int y);
		void passiveMouseMotion(int x, int y);
		void render();
		void reshape(int width, int height);
		void specialKey(int key, int x, int y);
	};
}

#endif
