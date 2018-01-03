#include <GL/glew.h>
#include "Texture.h"

#include <stdexcept>
#include <FreeImage.h>

using namespace cg1;
using namespace std;

Texture::Texture(const char * filename) {
    /* Load image */
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filename);
    FIBITMAP * bitmap = FreeImage_Load(format, filename, 0);
    if (!bitmap)
        throw runtime_error("Image loading failed.");
        
    /* Get metadata */
    int bpp = FreeImage_GetBPP(bitmap);
    if (bpp != 8)
        throw runtime_error("Wrong image format (bpp must be 8)");
        
    FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(bitmap);
    if (colorType != FIC_RGB && colorType != FIC_RGBALPHA)
        throw runtime_error("Wrong image format (must be RGB / RGBA)");
    GLuint colorTypeGL = colorType == FIC_RGB ? GL_RGB : GL_RGBA;
    
    int width = FreeImage_GetWidth(bitmap);
    int height = FreeImage_GetHeight(bitmap);
        
    unsigned char * imageBytes = FreeImage_GetBits(bitmap);
    
    /* Pass on to OpenGL */
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    glTexImage2D(GL_TEXTURE_2D, 0, colorTypeGL, width, height, 0, colorTypeGL, GL_UNSIGNED_BYTE, imageBytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    /* Cleanup */
    FreeImage_Unload(bitmap);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}
