#include "ktx2container.h"
#include "ktx2exception.h"

#include <filesystem>
#include <iostream>

namespace
{
    void RaiseKTXException(KTX2Exception const& Exception)
    {
        throw Exception;
    }
    
    class KTXStandardException final: public KTX2Exception
    {
        public:
        KTXStandardException(KTX_error_code Error) : m_Error {Error};
        {
        }
        
        void Message() override
        {
             std::cout << "KTX operation failed with error: " << Error << std::endl;
        }
        
        ~KTXStandardException() = default;
        KTXStandardException(KTXStandardException const& Other) = default;
        KTXStandardException& operator=(KTXStandardException const& Other) = default;
        KTXStandardException(KTXStandardException&& Other) = delete;
        KTXStandardException& operator=(KTXStandardException && Other) = delete;  
        
        private:
        KTX_error_code m_Error;
    };
    
    class KTXGLException final: public KTX2Exception
    {
        public:
        KTXGLException(GLenum GLErr) : m_GLErr {GLErr};
        {
        }
        
        void Message() override
        {
             std::cout << "KTX operation failed with GL error: " <<  GLErr << std::endl;
        }
        
        ~KTXGLException() = default;
        KTXGLException(KTXGLException const& Other) = default;
        KTXGLException& operator=(KTXGLException const& Other) = default;
        KTXGLException(KTXGLException&& Other) = delete;
        KTXGLException& operator=(KTXGLException && Other) = delete;  
        
        private:
        GLenum m_GLErr;
    };
};

KTX2TextureContainer::KTX2TextureContainer(std::string const& File)
{
    ktx2texture *texture;
    if (ktxTexture2_CreateFromNamedFile(File,  KTX_TEXTURE_CREATE_NO_FLAGS, &texture) != KTX_SUCCESS)
    {
        throw std::filesystem::filesystem_error;
    }
    m_pContainer {texture, ktxTexture2_Destroy};
}

void KTX2TextureContainer::GenerateGLTexture(GLuint &TextureOut,
                                             GLuint &TargetOut)
{
    GLenum glError = GL_OK;
    auto result = ktxTexture2_GLUpload(m_pContainer->get(), &TextureOut, TargetOut, &glError);
    switch (result)
    {
        case KTX_SUCCESS:
            break;
        case KTX_GL_ERROR:
            RaiseKTXException(KTXGLException {glError});
            break;
        default:
            RaiseKTXException(KTXStandardException {result});
            break;
    }
}
