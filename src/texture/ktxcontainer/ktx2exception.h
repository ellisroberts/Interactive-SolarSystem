#include <exception>

class KTX2Exception : public std::exception
{
    public:
    virtual ~KTX2Exception = 0;
    protected:
    KTX2Exception() = default;
    KTX2Exception(KTX2Exception const& Other) = default;
    KTX2Exception& operator=(KTX2Exception const& Other) = default;
    KTX2Exception(KTX2Exception && Other) = delete;
    KTX2Exception& operator=(KTX2Exception && Other) = delete;
};
