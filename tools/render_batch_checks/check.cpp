#include <lib/thrashrenderer.h>
#include <lib/opaque_policy.h>
#include <cassert>
#include <iostream>
#include <random>
#include <limits>
using R=win32::ThrashRenderer;
using namespace win32;
int main(){
 R::Batch root{},b{};
#define REASON(field,bit) b=root;b.field=!root.field;assert(root.differenceMask(b)==(1u<<bit));
 REASON(texture,0) REASON(levels,1) REASON(format,2) REASON(wrapS,3) REASON(wrapT,3)
 REASON(zTest,4) REASON(zTestAlways,4) REASON(zBuffer,4) REASON(alphaBlend,5)
 REASON(cull,6) REASON(cullMode,6) REASON(chromaKey,7)
 REASON(clipMinX,8) REASON(clipMinY,8) REASON(clipMaxX,8) REASON(clipMaxY,8) REASON(fogTable,9)
 b=root;b.gamma=-0.f;assert(root.differenceMask(b)==(1u<<10));
 b=root;b.end=123;b.opaqueAlpha=true;assert(root.differenceMask(b)==0);
 root.gamma=std::numeric_limits<float>::quiet_NaN();b=root;assert(root.differenceMask(b)==0);
 for(int format=0;format<4;++format)for(size_t offset=0;offset<4;++offset){
  std::vector<uint8_t> bytes(4*21+4,255);auto p=bytes.data()+offset;
  assert(opaque::textureAlphaIsOne(p,21,format));
  if(format==0)p[20*4+3]=254;
  if(format==2)p[20*2+1]&=0x7f;
  if(format==3)p[20*2+1]&=0xef;
  assert(opaque::textureAlphaIsOne(p,21,format)==(format==1));
 }
 assert(!opaque::textureAlphaIsOne(nullptr,1,1));
 uint8_t byte=255;assert(!opaque::textureAlphaIsOne(&byte,0,1));
 ThrashVertex v{};v.color=0xffffffff;v.oow=1;v.combine[1]=1;
 assert(opaque::vertexAlphaIsOne(v,true));assert(!opaque::vertexAlphaIsOne(v,false));
 v.combine[1]=0;assert(opaque::vertexAlphaIsOne(v,false));
 v.color=0xfeffffff;assert(!opaque::vertexAlphaIsOne(v,true));v.color=0xffffffff;
 v.combine[1]=2;assert(!opaque::vertexAlphaIsOne(v,true));v.combine[1]=1;
 v.u=std::numeric_limits<float>::quiet_NaN();assert(!opaque::vertexAlphaIsOne(v,true));v.u=0;
 v.z=std::numeric_limits<float>::infinity();assert(!opaque::vertexAlphaIsOne(v,true));v.z=0;
 v.u=65537;assert(!opaque::vertexAlphaIsOne(v,true));v.u=0;
 for(float oow:{-1.f,0.f,1e-20f,1e20f}){v.oow=oow;assert(!opaque::vertexAlphaIsOne(v,true));}v.oow=1;
 for(float ref:{0.f,0.5f,0.99f})assert(opaque::eligible(true,false,ref,true,true));
 for(float ref:{-1.f,254.f/255.f,1.f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()})assert(!opaque::eligible(true,false,ref,true,true));
 assert(!opaque::eligible(true,true,0,true,true));assert(!opaque::eligible(false,false,0,true,true));assert(!opaque::eligible(true,false,0,false,true));
 assert(!opaque::eligible(true,false,0,true,false));
 std::mt19937 rng(119);size_t eligible=0;
 for(size_t i=0;i<1000000;++i){
  const unsigned alpha=rng()%256,ta=rng()%256;const bool combine=rng()%2;
  v.color=(alpha<<24)|0xffffff;v.combine[1]=combine;
  float ref=float(rng()%256)/255.f;
  bool fast=opaque::eligible(opaque::vertexAlphaIsOne(v,ta==255),false,ref,true,true);
  float actual=float(alpha)/255.f;if(combine)actual*=float(ta)/255.f;
  if(fast){assert(actual==1.f&&actual>ref);++eligible;}
 }
 assert(eligible>1000);
 std::cout<<"PASS: conservative opaque classification over 1,000,000 randomized inputs; all formats/mip alpha, unaligned bytes, vertex/texture alpha combination, invalid inputs/ref/chroma, boundary categories; eligible "<<eligible<<"\n";
}
