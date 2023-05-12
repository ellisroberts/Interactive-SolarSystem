#include "texture/texturecontainer.h"

#include <filesystem>
#include <ktx.h>
#include <memory>
#include <string>
#include <vector>

#define GET_KTX_TEXTURE(KtxPath) [](std::filesystem::path const& KtxFilePath) \
                                     { \
                                         ktxTexture *texture = nullptr; \
                                         if (ktxTexture_CreateFromNamedFile(KtxFilePath.c_str(), \
                                                                            KTX_TEXTURE_CREATE_NO_FLAGS, \
                                                                            &texture) != KTX_SUCCESS) \
                                         { \
                                             throw std::filesystem::filesystem_error {KtxFilePath.string() + " Not Found", std::error_code{}}; \
                                         } \
                                         return texture; \
                                      }(KtxPath)

class KTXTextureContainer final : public TextureContainer
{
public:
    explicit KTXTextureContainer(std::filesystem::path const& KtxFilePath)
                                 : m_AssociatedFileName {KtxFilePath},
                                   m_pContainer {GET_KTX_TEXTURE(KtxFilePath),
                                                 [](ktxTexture *Text){ktxTexture_Destroy(Text);}}
    {
    }
    void GenerateGLTexture(GLuint &TextureOut,
                           GLuint &TargetOut) const override;
    //Delete copy and move operations
    KTXTextureContainer(KTXTextureContainer&& Other) = delete;
    KTXTextureContainer& operator=(KTXTextureContainer&& Other) = delete;
private:
    std::unique_ptr<ktxTexture, void (*)(ktxTexture*)> m_pContainer;
    std::string const m_AssociatedFileName = "";
};
