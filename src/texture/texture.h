#include <cstdint>
#include <GL/glew.h>
#include <string>
#include <vector>

class Texture
{
public:
	Texture(GLenum InternalFormat);
	//Load the texture from KTX2 container file
    void LoadContainer(std::string KTX2File);
    //Return the Pixel Data for comparison
    TexelData GetPixelData();
    //Bind the texture object to the opengl state
    void BindObject();
    //Return the binding state of the texture object
    bool IsObjectBound();
    GLint GetParameter(GLenum ParamName);
    void SetParameter(GLenum ParamName, GLint ParamValue);
    GLenum GetStorageType() { return m_Type; }
    GLuint GetNumLevels() { return m_MipMapLevels; }
    GLuint GetWidth() { return m_Width; }
    GLuint GetHeight() { return m_Height; }
    GLuint GetDepth() { return m_Depth; }
	~Texture();
private:
	GLenum m_Type;
	GLuint m_MipMapLevels;
	GLuint m_Width;
	GLuint m_Height;
	GLuint m_Depth;
};
