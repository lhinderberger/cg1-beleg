#ifndef CG1_MODEL
#define CG1_MODEL

#include <list>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Light.h"

namespace cg1 {
	class Application;
    class Model {
    private:
    	Application * application;
        glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        
    public:
        glm::mat4 modelMatrix;
        
        Model(Application * application);
        
        virtual std::list<PointLight> getPointLights();
        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) = 0;

        void setColor(const glm::vec4 & color);
        void setModelAndNormalMatrixUniform(glm::mat4 processedModelMatrix);

		inline Application * getApplication() const { return application; }
        const inline glm::vec4 & getColor() const { return color; }
    };
};

#include "Application.h"

#endif
