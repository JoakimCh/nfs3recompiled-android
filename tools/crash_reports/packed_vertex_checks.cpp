#include "packed_vertex.h"
#include <cstdint>
#include <cstring>
#include <cstdio>
int main() {
    alignas(16) unsigned char bytes[32] = {};
    const std::uint32_t patterns[] = {0,0x80000000,0x3f800000,0x7f7fffff,1,0x00800000,0x7f800000,0xff800000,0x7fc12345};
    unsigned cases=0;
    for(unsigned offset=0;offset<8;++offset)
      for(unsigned k=0;k<9;++k) {
        std::uint32_t expected[3]={patterns[k],patterns[(k+1)%9],patterns[(k+2)%9]},actual[3];
        std::memcpy(bytes+offset,expected,12);
        auto v=nfs3hp::readPackedVertex(bytes+offset);
        std::memcpy(actual,v.data(),12);
        if(std::memcmp(expected,actual,12))return 1;
        ++cases;
      }
    std::printf("%u packed vertex bit-pattern/alignment cases passed\n",cases);
}
