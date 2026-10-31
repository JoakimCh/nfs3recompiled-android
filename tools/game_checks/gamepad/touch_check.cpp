#include <lib/touch_input.h>
#include <cassert>
#include <map>
#include <iostream>
#include <thread>
using namespace win32::touchinput;
int main(){
 std::map<uint32_t,uint32_t> memory;unsigned reads=0;
 auto read=[&](uint32_t p){++reads;return memory[p];};
 memory[0x79c340+8]=0x41001e04; // Accelerator initially A.
 set(2,true);assert(held()==0);active(true);set(2,true);
 assert(matches(0x1e04,read));assert(!matches(0x4804,read)); // Glyph ignored, scan respected.
 memory[0x79c340+8]=0x20000302; // Remap while held to device2 button4.
 assert(!matches(0x1e04,read));assert(matches(0x20000302,read));
 memory[0x79c340+8]=0x17f0001; // Axis Y lower half; upper must stay untouched.
 assert(matches(0x17f0001,read));assert(!matches(0x180ff01,read));
 memory[0x79c340+8]=0x01002003;assert(matches(0x01002003,read));
 memory[0x79c340+8]=0;assert(!matches(0,read));assert(!matches(0x01002003,read));
 memory[0x79c340+8]=0x1f04;assert(matches(0x1f04,read));
 memory[0x79c370+8]=0x20000202;assert(!matches(0x20000202,read)); // No player2 table leak.
 active(false);assert(held()==0);assert(!matches(0x1f04,read));
 active(true);assert(held()==0);set(2,true);set(2,false);assert(held()==0);
 set(13,true);set(999,true);assert(held()==0);
 reads=0;assert(!matches(0x1f04,read)&&reads==0); // Idle path never reads guest tables.
 constexpr unsigned slots[13]={1,0,2,3,6,8,9,0x2e,7,0x2d,5,0xb,0xa};
 for(unsigned action=0;action<13;++action){
  memory[0x79c340+4*slots[action]]=0x100*(action+1)+4;
  set(action,true);assert(matches(0x100*(action+1)+4,read));set(action,false);
 }
 std::thread ui([]{for(unsigned i=0;i<100000;++i){set(i%13,true);set(i%13,false);}});
 for(unsigned i=0;i<10000;++i){active(false);active(true);}ui.join();active(false);
 assert(!(state().load()&(Active|Actions)));auto stopped=state().load();set(0,true);assert(state().load()==stopped);
 active(true);auto stale=state().load();active(false);active(true);auto expected=stale;
 assert(!state().compare_exchange_strong(expected,stale|1u));active(false);
 std::cout<<"PASS live remaps for keyboard/button/axis/POV, glyph normalization, split-player isolation, 13 actions, unbound/invalid inputs, release/menu transitions, idle no-read path and concurrent UI/lifecycle updates\n";
}
