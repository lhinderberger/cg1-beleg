#include <GL/glew.h>
#include "Texture.h"

#include <iostream>
#include <stdexcept>
#include <FreeImage.h>

using namespace cg1;
using namespace std;

Texture::Texture(const char * filename) {
    /* Load image */
    cout << "Loading " << filename << endl;
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filename);
    FIBITMAP * bitmap = FreeImage_Load(format, filename, 0);
    if (!bitmap)
        throw runtime_error("Image loading failed.");
    FIBITMAP * cBitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(bitmap);
    if (!cBitmap)
        throw runtime_error("Image conversion failed.");
        
    /* Get metadata */    
    int width = FreeImage_GetWidth(cBitmap);
    int height = FreeImage_GetHeight(cBitmap);
        
    unsigned char * imageBytes = FreeImage_GetBits(cBitmap);
    
    /* Pass on to OpenGL */
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, imageBytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    /* Cleanup */
    FreeImage_Unload(cBitmap);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}
