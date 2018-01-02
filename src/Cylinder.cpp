#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Cylinder.h"

#include <cstring>
#include <iostream>

#define PI 3.1415

using namespace cg1;
using namespace glm;
using namespace std;

Cylinder::Cylinder(Application * application, float radius, float height, int subdivisions)
	: Model(application) {
	
	this->radius = radius;
	this->height = height;
	this->subdivisions = subdivisions;
	
	// Create vertices and normals for Cap and Side
	int nCapVertices = subdivisions * 6*3; // One triangle per subdivision
	float capVertices[nCapVertices];
	int nSideVertices = subdivisions * 6*6; // Two triangles per subdivision
	float sideVertices[nSideVertices];
	for (int i = 0; i < subdivisions; i++) {
        float angleRadians = (float)i/(float)subdivisions * 2 * PI;
        float nextAngleRadians = (float)(i+1)/(float)subdivisions * 2 * PI;
        
        float x = radius * sin(angleRadians);
        float z = radius * cos(angleRadians);
        float nextX = radius * sin(nextAngleRadians);
        float nextZ = radius * cos(nextAngleRadians);
        
        // Create the Cap triangle for the current subdivision
        float capTriangle[18] = {
            // Position     //Normal
            0,0,0,          0,1,0,            
            x,0,z,          0,1,0,            
            nextX,0,nextZ,  0,1,0
        };
        memcpy(capVertices + i*18, capTriangle, 18 * sizeof(float));
        
        // Create the side "quad" for the current subdivision
        float normalAngleRadians = ((float)i + 0.5f)/(float)subdivisions * 2 * PI;
        float normalX = sin(normalAngleRadians);
        float normalZ = cos(normalAngleRadians);
        
        float sideTriangles[36] = {
            // Position             // Normal
            x,0,z,                  normalX,0,normalZ,
            nextX,0,nextZ,          normalX,0,normalZ,
            x,height,z,             normalX,0,normalZ,
            
            x,height,z,             normalX,0,normalZ,
            nextX,0,nextZ,          normalX,0,normalZ,
            nextX,height,nextZ,     normalX,0,normalZ,
        };
        memcpy(sideVertices + i*36, sideTriangles, 36 * sizeof(float));
    }
    
    // Create Cap VAO
	capVAO = VAO::create(capVertices, nCapVertices);
	capVAO->setupAttribPointer(0,3,6);
    //vao->setupAttribPointer(1,3,6,3); TODO: Enable for lighting
    
    // Create Side VAO
	sideVAO = VAO::create(sideVertices, nSideVertices);
	sideVAO->setupAttribPointer(0,3,6);
    //vao->setupAttribPointer(1,3,6,3); TODO: Enable for lighting
}

void Cylinder::render(glm::mat4 parentModelMatrix) {    
    // Set color
    const vec4 & color = getColor();
    glVertexAttrib4f(1, color.r, color.g, color.b, color.a);
    
    // === Render Caps
    capVAO->bind();
    
    // Render flipped top cap first
    setModelMatrixUniform(
        parentModelMatrix * modelMatrix *
        translate(mat4(), vec3(0,height,0)) *
        rotate(mat4(), radians(180.0f), vec3(1,0,0))
    );
    glDrawArrays(GL_TRIANGLES, 0, subdivisions*3);
    
    // Reset model matrix and render bottom cap
    setModelMatrixUniform(parentModelMatrix * modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, subdivisions*3);
    
    // === Render side
    sideVAO->bind();
    glDrawArrays(GL_TRIANGLES, 0, subdivisions*6);
}
