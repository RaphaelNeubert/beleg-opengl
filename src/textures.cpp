#include "textures.hpp"
#include "common.hpp"
#include <FreeImage.h>
#include <freeglut.h>


void loadCube1Texture()
{
    FreeImage_Initialise(TRUE);
    FIBITMAP *bitmapData;
    int bitmapWidth,bitmapHeight;
    BYTE *bitmapBits;
    FREE_IMAGE_FORMAT bitmapFormat=FIF_UNKNOWN;
    bitmapFormat=FreeImage_GetFileType("./textures/cube1.jpg");
    bitmapData=FreeImage_Load(bitmapFormat,"./textures/cube1.jpg");
    bitmapWidth=FreeImage_GetWidth(bitmapData);
    bitmapHeight=FreeImage_GetHeight(bitmapData);
    bitmapBits=FreeImage_GetBits(bitmapData);

    glBindTexture(GL_TEXTURE_2D,Textures[texCube1]);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexStorage2D(GL_TEXTURE_2D,0,GL_RGB,bitmapWidth,bitmapHeight);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, bitmapWidth,bitmapHeight,0,GL_BGR,
                                                GL_UNSIGNED_BYTE,bitmapBits);
    glGenerateMipmap(GL_TEXTURE_2D);
    FreeImage_Unload(bitmapData);
}

void loadCube2Texture()
{
    FreeImage_Initialise(TRUE);
    FIBITMAP *bitmapData;
    int bitmapWidth,bitmapHeight;
    BYTE *bitmapBits;
    FREE_IMAGE_FORMAT bitmapFormat=FIF_UNKNOWN;
    bitmapFormat=FreeImage_GetFileType("./textures/cone1.jpg");
    bitmapData=FreeImage_Load(bitmapFormat,"./textures/cone1.jpg");
    bitmapWidth=FreeImage_GetWidth(bitmapData);
    bitmapHeight=FreeImage_GetHeight(bitmapData);
    bitmapBits=FreeImage_GetBits(bitmapData);

    glBindTexture(GL_TEXTURE_2D,Textures[texCube2]);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexStorage2D(GL_TEXTURE_2D,0,GL_RGB,bitmapWidth,bitmapHeight);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, bitmapWidth,bitmapHeight,0,GL_BGR,
                                                GL_UNSIGNED_BYTE,bitmapBits);
    glGenerateMipmap(GL_TEXTURE_2D);
    FreeImage_Unload(bitmapData);
}
