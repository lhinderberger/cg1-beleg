#include <GL/glew.h>
#include "Cylinder.h"

#include <iostream>

using namespace cg1;
using namespace glm;
using namespace std;

Cylinder::Cylinder(Application * application, float radius, float height, int subdivisions)
	: Model(application) {
    nVertices = 2*(subdivisions+1) + 2;
    vector<vec3> vertices(nVertices);
    triangleIndexes.resize(subdivisions*6);
    triangleStripIndexes.resize((subdivisions+1)*2);

    vertices[0] = vec3(0.0f,0.0f,0.0f);

    for (int y = 0; y < 2; y++) {
        for (int i = 0; i <= subdivisions; i++) {
            float angleRadians = (float)i/(float)subdivisions * 2 * 3.1415;
            vertices[y*subdivisions+i+1] = vec3(radius * sin(angleRadians), y * height, radius * cos(angleRadians));
        }
    }

    vertices[nVertices-1] = vec3(0.0f,height,0.0f);

    for (int i = 0; i < subdivisions; i++) {
        triangleIndexes[i*6] = 0;
        triangleIndexes[i*6+1] = 1+i;
        triangleIndexes[i*6+2] = 1+(i+1)%subdivisions;

        triangleIndexes[i*6+3] = nVertices-1;
        triangleIndexes[i*6+4] = i+1+subdivisions;
        triangleIndexes[i*6+5] = i+2+subdivisions;
    }

    for (int i=0; i <= subdivisions; i++) {
        triangleStripIndexes[i*2] = i%subdivisions + 1;
        triangleStripIndexes[i*2+1] = triangleStripIndexes[i*2]+subdivisions;
    }

    vao = VAO::create(vertices);
}

void Cylinder::render(glm::mat4 parentModelMatrix) {
    Model::render(parentModelMatrix);
    
    vao->bind();

    const vec4 & color = getColor();
    glVertexAttrib4f(1, color.r, color.g, color.b, color.a);
    glDrawElements(GL_TRIANGLES, triangleIndexes.size(), GL_UNSIGNED_INT, &(triangleIndexes[0]));
    glDrawElements(GL_TRIANGLE_STRIP, triangleStripIndexes.size(), GL_UNSIGNED_INT, &(triangleStripIndexes[0]));
}
