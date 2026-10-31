#ifndef LIB_OPAQUE_POLICY_H
#define LIB_OPAQUE_POLICY_H
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace win32::opaque {
// Original guest bytes, BEFORE 1555 rotation or the GPU's format swizzles.
// Every supplied mip level is included, not just the top-level picture.
inline bool textureAlphaIsOne(const uint8_t* bytes,size_t texels,int format) {
    if(!bytes||!texels)return false;
    if(format==1)return true; // RGB565: alpha is implicitly one.
    if(format==0){for(size_t i=0;i<texels;++i)if(bytes[i*4+3]!=255)return false;return true;}
    if(format==2){for(size_t i=0;i<texels;++i)if(!(bytes[i*2+1]&0x80))return false;return true;}
    if(format==3){for(size_t i=0;i<texels;++i)if((bytes[i*2+1]&0xf0)!=0xf0)return false;return true;}
    return false;
}
template<class Vertex> bool vertexAlphaIsOne(const Vertex& v,bool textureOpaque) {
    // Bound coordinates keep the same well-defined normalized-texture sampling
    // domain on both shaders; unknown/nonfinite data uses the original shader.
    return (v.color>>24)==255 && (v.combine[1]==0 || (v.combine[1]==1&&textureOpaque))
        && std::isfinite(v.x)&&std::isfinite(v.y)&&std::isfinite(v.z)
        && std::isfinite(v.u)&&std::isfinite(v.v)&&std::isfinite(v.oow)
        && std::fabs(v.u)<=65536.f && std::fabs(v.v)<=65536.f
        && v.oow>=1.f/65536.f && v.oow<=65536.f;
}
inline bool eligible(bool alphaIsOne,bool chromaKey,float alphaRef,bool validTexture,bool standardBlend) {
    // Ref is normally byte/255. Leave a generous margin below alpha one;
    // pathological references, including NaN, fall back to the general shader.
    return alphaIsOne && !chromaKey && validTexture && standardBlend && alphaRef>=0.f && alphaRef<=0.99f;
}
}
#endif
