#include "texturecontainer.h"

#include <exception>
#include <ktx.h>
#include <memory>
#include <string>
#include <vector>

//Invariant: Object will always container a valid pointer to a ktx structure
class KTX2TextureContainer final : public TextureContainer
{
public:
    KTX2TextureContainer(std::string const& File);
    void GenerateGLTexture(GLuint &TextureOut,
                           GLuint &TargetOut) override;
    //Delete copy and move operations
    KTX2TextureContainer(KTX2TextureContainer&& Other) = delete;
    KTX2TextureContainer& operator=(KTX2TextureContainer&& Other) = delete;
private:
    std::unique_ptr<ktx2texture, void (ktx2texture*)> m_pContainer;
};
