#include "ktxcontainer.h"
#include "ktxexception.h"

#include <GL/glew.h>
#include <iostream>

void KTXTextureContainer::GenerateGLTexture(GLuint &TextureOut,
                                            GLenum &TargetOut)
{
    GLenum glError = GL_NO_ERROR;
    auto result = ktxTexture_GLUpload(m_pContainer.get(), &TextureOut, &TargetOut, &glError);
    if (result != KTX_SUCCESS)
    {
        throw KTXException {m_AssociatedFileName, result, glError};
    }
}
