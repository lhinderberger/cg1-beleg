#ifndef CG1_TEXTURE_H
#define CG1_TEXTURE_H

#include <GL/glew.h>

namespace cg1 {
    class Texture {
    private:
        GLuint id;
        
    public:
        Texture(const char * filename);
        ~Texture();
        
        void bind();
        
        inline GLuint getId() const { return id; }
    };
};

#endif
