from pathlib import Path
import subprocess
import sys,tempfile
r=Path(__file__).resolve().parents[3];work=Path(sys.argv[1]) if len(sys.argv)>1 else Path(tempfile.mkdtemp(prefix='nfs3-touch-check-'));work.mkdir(parents=True,exist_ok=True);src=(r/'src/nfs3hp/native_controls_pipeline.cpp').read_text()
names=['buttonHeld','hatPointing','axisAmount','keyHeld','controlHeld'];parts=[]
for name in names:
 marker=f'void {name}(win32::WinApplication* app, x86::CPU& cpu)\n{{';a=src.index(marker)+len(marker);b=src.index('\n    }',a)+6
 branch=src[a:b];parts.append(f'void {name}(App* app,CPU& cpu){{'+branch+'throw 1;}')
code='''#include <lib/touch_input.h>
#include <cstdint>
#include <map>
#include <cassert>
#include <iostream>
using reg32=uint32_t;
struct App{std::map<uint32_t,uint32_t> memory;template<class T>T getMemory(uint32_t address){auto i=memory.find(address);return i==memory.end()?0:T(i->second);}};
struct CPU{uint32_t eax,esp,ecx,edx,ebp,flags;};
constexpr uint32_t kClearedKey=0x56484f;
void putByte(App* a,uint32_t p,uint32_t v){a->memory[p]=v&255;}
'''+ '\n'.join(parts)+'''
int main(){
using namespace win32::touchinput;
void(*handlers[])(App*,CPU&)={buttonHeld,hatPointing,axisAmount,keyHeld,controlHeld};
uint32_t bindings[]={0x10000302,0x01002003,0x17f0001,0x41001e04,0x42003004};
for(int i=0;i<5;++i){App app;app.memory[0x79c348]=bindings[i];app.memory[kClearedKey]=127;
CPU c{bindings[i],0x1000,11,22,33,0xabcd};active(true);set(2,true);handlers[i](&app,c);
assert(c.eax==255&&c.esp==0x1004&&c.ecx==11&&c.edx==22&&c.ebp==33&&c.flags==0xabcd);
assert(app.memory[kClearedKey]==(i==3?0:127));
set(2,false);c={bindings[i],0x1000,11,22,33,0xabcd};bool fallback=false;try{handlers[i](&app,c);}catch(int){fallback=true;}
assert(fallback&&c.eax==bindings[i]&&c.esp==0x1000&&c.ecx==11&&c.edx==22&&c.ebp==33&&c.flags==0xabcd);
}
std::cout<<"PASS exact production touch entry branches: guest return/stack, preserved registers/flags, key-clear side effect and no-touch fallthrough in all five handlers\\n";
}
'''
p=(work/'entry-check.cpp');p.write_text(code)
subprocess.run(['g++','-std=c++17','-O2','-fsanitize=undefined','-I',str(r/'include'),str(p),'-o',str(work/'entry-check')],check=True)
subprocess.run([str(work/'entry-check')],check=True)
