#pragma once

#include <exception>
#include <filesystem>
#include <boost/format.hpp>
#include <GL/glew.h>

class KTXException : public std::runtime_error
{
    public:

    KTXException(std::filesystem::path const& Path, KTX_error_code KtxError, GLenum GlError)
                 : std::runtime_error {boost::str(boost::format("Operation on Ktx file %1% failed with KTX error code %2% GL Error Code %3%") % Path
                                                                                                                                            % KtxError
                                                                                                                                            % GlError)},
                   m_Path {Path},
                   m_KtxError {KtxError},
                   m_GlError {GlError}
    {
    }
    
    KTXException(KTXException const& Other) = default;
    KTXException& operator=(KTXException const& Other) = default;
    KTXException(KTXException && Other) = delete;
    KTXException& operator=(KTXException && Other) = delete;
    ~KTXException() = default;
    
    auto GetPath() {return m_Path;}
    auto GetKtxError() {return m_KtxError;}
    auto GetGlError() {return m_GlError;}
    
    private:
    std::filesystem::path m_Path;
    KTX_error_code m_KtxError;
    GLenum m_GlError;
};
