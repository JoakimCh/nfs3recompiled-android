#!/usr/bin/env python3
# Requires Linux Mesa EGL surfaceless/llvmpipe, g++, and GLES headers (NDK generic sysroot is sufficient).
# Uses verbatim production initGl/compileShaders/drawPending and shader sources, not a rewritten renderer.
from pathlib import Path
import sys,tempfile
SOURCE=Path(__file__).resolve().parents[2]
GLES_INCLUDE=Path(sys.argv[1]) if len(sys.argv)>1 else Path('/usr/include')
with tempfile.TemporaryDirectory(prefix='nfs3-gles-check-') as directory:
 WORK=Path(directory)
 from pathlib import Path
 import re
 r=SOURCE;s=(r/'src/lib/thrashrenderer.cpp').read_text();h=(r/'include/lib/thrashrenderer.h').read_text()
 def function(mark):
  a=s.index(mark);return s[a:s.index('\n}',a)+2]
 parts=[function(mark) for mark in ['static bool needsDepthSteps','static void fogW','static GLuint compileShader','void ThrashRenderer::initGl()','void ThrashRenderer::compileShaders','void ThrashRenderer::drawPending']]
 parts=[p.replace('ThrashRenderer::','Harness::') for p in parts]
 loc=h[h.index('    struct Locations'):h.index('    bool                    m_depth16;')]
 shaders=s[s.index('static const char g_preamble'):s.index('static const x86::reg32 s_maxVertices')]
 body=shaders+'\n'+ '\n'.join(parts)
 extra='''
 extern "C" void* checkCreate(unsigned target,unsigned w,unsigned h,const unsigned* textures,unsigned count){
  auto p=new Harness{};p->renderer={target,w,h};p->m_renderer=&p->renderer;
  p->m_glTextures.assign(textures,textures+count);p->initGl();return p;
 }
 extern "C" unsigned long long checkFastCount(){return perf::snapshot()[perf::OpaqueDraws];}
extern "C" int checkAvailable(void* ptr){return static_cast<Harness*>(ptr)->m_opaqueProgram!=0;}
 extern "C" unsigned checkFramebuffer(void* ptr){return static_cast<Harness*>(ptr)->m_framebuffer;}
 extern "C" void checkDraw(void* ptr,void* vertices,unsigned count,const int* batches,unsigned batchCount,int optimize,float ref,float fog){
  auto p=static_cast<Harness*>(ptr);ThrashDraw draw{};draw.vertices=static_cast<ThrashVertex*>(vertices);draw.vertexCount=count;
  draw.width=64;draw.height=64;draw.alphaTestRef=ref;draw.fogColor[0]=0.1f;draw.fogColor[1]=0.6f;draw.fogColor[2]=0.2f;draw.chromaKeyColor=0;
  std::array<float,64> table{};table.fill(fog);draw.fogTables.push_back(table);table.fill(1.f-fog);draw.fogTables.push_back(table);
  for(unsigned i=0;i<batchCount;i++){
   auto v=batches+12*i;ThrashRenderer::Batch b{};b.end=v[0];b.texture=v[1];b.format=v[2];b.opaqueAlpha=v[3];
   b.wrapS=v[4]&1;b.wrapT=v[4]&2;b.zTest=v[5]&1;b.zBuffer=v[5]&2;b.zTestAlways=v[5]&4;
   b.alphaBlend=v[6];b.chromaKey=v[7];b.fogTable=v[8];b.gamma=v[9]/100.f;
   b.clipMinX=0;b.clipMinY=0;b.clipMaxX=v[10];b.clipMaxY=v[11];b.levels=2;
   draw.batches.push_back(b);
  }
  auto program=p->m_opaqueProgram;if(!optimize)p->m_opaqueProgram=0;
  p->drawPending(draw);p->m_opaqueProgram=program;
 }
 extern "C" void checkDestroy(void* ptr){auto p=static_cast<Harness*>(ptr);
  glDeleteProgram(p->m_program);glDeleteProgram(p->m_opaqueProgram);glDeleteSamplers(4,p->m_samplers);
  glDeleteFramebuffers(1,&p->m_framebuffer);glDeleteRenderbuffers(1,&p->m_depthBuffer);
  glDeleteBuffers(1,&p->m_vertexBuffer);glDeleteVertexArrays(1,&p->m_vertexArray);delete p;
 }
 '''
 allcode=body+extra
 names=sorted(set(re.findall(r'\b(gl[A-Z]\w*)\s*\(',allcode)))
 # Keep host libc headers ahead of NDK's generic API declarations.
 pre='''#include <lib/thrashrenderer.h>
 #include <lib/perfstats.h>
 #include <lib/opaque_policy.h>
 #include <GLES3/gl3.h>
 #include <string>
 #include <cstring>
 #include <cmath>
 #include <cstdio>
 extern "C" void* eglGetProcAddress(const char*);
 #define SDL_getenv std::getenv
 #define SDL_strstr std::strstr
 #define SDL_strcmp std::strcmp
 #define SDL_LOG_CATEGORY_APPLICATION 0
 #define SDL_LOG_CATEGORY_RENDER 0
 #define SDL_LogInfo(...) ((void)0)
 #define SDL_LogError(...) std::fprintf(stderr,"GL shader error\\n")
 #define NFS_GLSL_PREAMBLE "#version 300 es\\nprecision highp float;\\nprecision highp int;\\nprecision highp sampler2D;\\n"
 '''
 for n in names:pre+=f'#define {n}(...) reinterpret_cast<decltype(&::{n})>(eglGetProcAddress("{n}"))(__VA_ARGS__)\n'
 cls='''namespace win32 {
 inline void loadGlFunctions(){}
 struct Harness {
  using Batch=ThrashRenderer::Batch;
  struct Renderer {unsigned m_texture,m_width,m_height;} renderer,*m_renderer;
  unsigned m_program=0,m_opaqueProgram=0,m_framebuffer=0,m_depthBuffer=0,m_vertexArray=0,m_vertexBuffer=0,m_samplers[4]{};
  bool m_depth16=false;std::vector<unsigned> m_glTextures;
 '''+loc+'''
  void initGl();void compileShaders(int,const char*);void drawPending(const ThrashDraw&);
 };
 '''
 (WORK/'gl_harness.cpp').write_text(pre+cls+body+extra+'\n}\n')
 print('Generated harness with verbatim production initGl/compileShaders/drawPending and shader source')

 import subprocess
 subprocess.run(['g++','-std=c++17','-O2','-fPIC','-shared','-DWITH_MMX','-I',str(SOURCE/'include'),'-I',str(SOURCE/'sdl3/include'),'-idirafter',str(GLES_INCLUDE),str(WORK/'gl_harness.cpp'),'-l:libEGL.so.1','-o',str(WORK/'gl_harness.so')],check=True)
 import ctypes as C,os
 os.environ['EGL_PLATFORM']='surfaceless'
 e=C.CDLL('libEGL.so.1');e.eglGetProcAddress.argtypes=[C.c_char_p];e.eglGetProcAddress.restype=C.c_void_p
 get=C.CFUNCTYPE(C.c_void_p,C.c_uint,C.c_void_p,C.POINTER(C.c_int))(e.eglGetProcAddress(b'eglGetPlatformDisplayEXT'))
 d=get(0x31DD,None,None)
 def ef(n,rest,args):
  f=getattr(e,n);f.restype=rest;f.argtypes=args;return f
 I=C.c_int;P=C.c_void_p
 assert ef('eglInitialize',I,[P,C.POINTER(I),C.POINTER(I)])(d,None,None)
 assert ef('eglBindAPI',I,[C.c_uint])(0x30A0)
 attrs=(I*15)(0x3033,1,0x3040,0x40,0x3024,8,0x3023,8,0x3022,8,0x3021,8,0x3038,0,0);cfg=P();n=I()
 assert ef('eglChooseConfig',I,[P,C.POINTER(I),C.POINTER(P),C.c_int,C.POINTER(I)])(d,attrs,C.byref(cfg),1,C.byref(n)) and n.value
 surf=ef('eglCreatePbufferSurface',P,[P,P,C.POINTER(I)])(d,cfg,(I*5)(0x3057,64,0x3056,64,0x3038))
 ctx=ef('eglCreateContext',P,[P,P,P,C.POINTER(I)])(d,cfg,None,(I*3)(0x3098,3,0x3038))
 assert surf and ctx and ef('eglMakeCurrent',I,[P,P,P,P])(d,surf,surf,ctx)
 def gl(n,rest,args):return C.CFUNCTYPE(rest,*args)(e.eglGetProcAddress(n.encode()))
 print(gl('glGetString',C.c_char_p,[C.c_uint])(0x1f01).decode())
 import struct,random
 U=C.c_uint;F=C.c_float
 os.environ['NFS_PERF_STATS']='1'
 api=C.CDLL(str(WORK/'gl_harness.so'))
 api.checkCreate.argtypes=[U,U,U,C.POINTER(U),U];api.checkCreate.restype=P
 api.checkFramebuffer.argtypes=[P];api.checkFramebuffer.restype=U
 api.checkAvailable.argtypes=[P];api.checkAvailable.restype=I
 api.checkFastCount.restype=C.c_uint64;api.checkFastCount.argtypes=[]
 api.checkDraw.argtypes=[P,P,U,C.POINTER(I),U,I,F,F];api.checkDestroy.argtypes=[P]
 gen=gl('glGenTextures',None,[I,C.POINTER(U)]);bind=gl('glBindTexture',None,[U,U]);param=gl('glTexParameteri',None,[U,U,I]);image=gl('glTexImage2D',None,[U,I,I,I,I,I,U,U,P])
 def texture(w,h,raw):
  t=U();gen(1,C.byref(t));bind(0xde1,t);param(0xde1,0x813d,1 if w>1 else 0)
  for level in range(2 if w>1 else 1):
   ww=max(1,w>>level);hh=max(1,h>>level);data=C.create_string_buffer(raw[:ww*hh*4]);image(0xde1,level,0x8058,ww,hh,0,0x1908,0x1401,data)
  return t.value
 raw=[]
 for kind in range(3):
  b=bytearray()
  for j in range(16):b+=bytes(((j*37)%256,(j*71)%256,(j*19)%256,((j*31)%256) if kind==1 else 255))
  raw.append(bytes(b))
 textures=(U*3)(*[texture(4,4,b) for b in raw]);target=texture(64,64,bytes(64*64*4))
 clear=gl('glClear',None,[U]);clearcolor=gl('glClearColor',None,[F,F,F,F]);cleardepth=gl('glClearDepthf',None,[F]);depthmask=gl('glDepthMask',None,[C.c_ubyte]);disable=gl('glDisable',None,[U]);fb=gl('glBindFramebuffer',None,[U,U]);read=gl('glReadPixels',None,[I,I,I,I,U,U,P]);error=gl('glGetError',U,[])
 rng=random.Random(119);cases=0
 for depth in [0,1]:
  os.environ['NFS_DEPTH16']=str(depth);harness=api.checkCreate(target,64,64,textures,3);assert harness and api.checkAvailable(harness)
  for case in range(160):
   verts=bytearray();batches=[]
   ref=[0,.5,254/255,1][case%4];fog=(case%5)/5
   for j in range(8):
    tex=(j+case)%3;alpha=255 if j%3 else 128;combine=(j+case)%2;chroma=int(j%5==0)
    flags=int(alpha==255 and (combine==0 or tex!=1))
    wrap=j%4;z=5000+j*7000;gamma=[100,130,75][(case+j)%3]
    for x,y in [(1+j,1+j),(63-j,2+j),(30,63-j)]:
     oow=[.5,1.,2.][j%3];u=(x/64*2-.5)*256*oow;v=(y/64*2-.5)*256*oow
     color=(alpha<<24)|rng.randrange(1<<24)
     verts+=struct.pack('<fffIfffBBBB',x,y,z,color,u,v,oow,1,combine,0,int(j%2))
    batches.extend([3*(j+1),tex,0,flags,wrap,3 if j%2 else 7,j%2,chroma,j%2,gamma,64 if j%3 else 48,64 if j%4 else 40])
   vb=C.create_string_buffer(bytes(verts));bb=(I*len(batches))(*batches)
   results=[]
   for optimize in [0,1]:
    fb(0x8d40,api.checkFramebuffer(harness));disable(0xc11);depthmask(1);clearcolor(.13,.21,.31,.5);cleardepth(1);clear(0x4000|0x100)
    before=api.checkFastCount()
    api.checkDraw(harness,vb,24,bb,8,optimize,ref,fog)
    if not optimize:assert api.checkFastCount()==before
    pix=(C.c_ubyte*(64*64*4))();read(0,0,64,64,0x1908,0x1401,pix);results.append(bytes(pix));assert error()==0,(case,depth)
   assert results[0]==results[1],('pixel mismatch',depth,case,max(abs(a-b) for a,b in zip(*results)))
   cases+=1
  api.checkDestroy(harness)
 assert api.checkFastCount()>0
 print('Actual optimized draws:',api.checkFastCount())
 print(f'PASS: {cases} paired scenes/{cases*2} full production GL submissions, general-only vs opaque-selected, bit-exact RGBA across {cases*64*64:,} pixels; depth quantization on/off, program switching, fog/gamma, blend/depth/scissor/wrap, chroma and alpha fallbacks')
