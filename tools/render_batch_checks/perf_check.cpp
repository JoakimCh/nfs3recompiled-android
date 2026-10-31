#include <lib/perfstats.h>
#include <cassert>
#include <iostream>
#include <thread>
#include <string>
using namespace win32;
int main(int argc,char** argv) {
    bool expected=argc>1 && std::string(argv[1])=="on";
    assert(perf::enabled()==expected);
    bool opaque=argc>2 && std::string(argv[2])=="opaque";
    assert(perf::opaqueEnabled()==opaque);
    auto t=perf::now();assert(t>0);
    perf::presented(t,640,480);perf::presented(t+33000000,640,480);
    perf::submitted(12,7,300,2000000,1000000);
    auto v=perf::snapshot();
    if(!expected){
        perf::timing(perf::RaceCalls,100,20,0);
        std::array<uint64_t,13> c{};c[0]=10;perf::boundaries(c,100,20,0);
        {perf::Scope scope(perf::RaceCalls);}
        assert(v[1]==0&&v[4]==0&&perf::snapshot()[perf::RaceCalls]==0&&perf::snapshot()[perf::AdjacentPairs]==0);
        std::cout<<"PASS disabled counters, phase timings, boundaries and experiment setting\n";return 0;
    }
    assert(v[1]==2&&v[2]==1&&v[3]==33000000&&v[13+33]==1);
    assert(v[4]==12&&v[5]==7&&v[6]==300&&v[7]==1&&v[8]==2000000&&v[9]==1000000);
    assert(v[11]==640&&v[12]==480);
    perf::active(false);perf::submitted(5,4,3,2,1);perf::presented(t+50000000,1,1);
    assert(perf::snapshot()[1]==2&&perf::snapshot()[4]==12);
    perf::active(true);perf::presented(t+10000000000ULL,800,600);
    assert(perf::snapshot()[2]==1); // Pause gap does not become a frame interval.
    perf::presented(t+12000000000ULL,800,600);
    assert(perf::snapshot()[10]==1&&perf::snapshot()[2]==1);
    std::thread writer([]{for(int i=0;i<100000;i++)perf::submitted(2,1,6,10,5);});
    for(int i=0;i<10000;i++){v=perf::snapshot();assert(v[4]-12==2*(v[5]-7));}
    writer.join();v=perf::snapshot();assert(v[4]==200012&&v[5]==100007&&v[6]==600300);
    auto c=perf::cpuNow();for(volatile int i=0;i<100000;++i){}assert(perf::cpuNow()>=c);
    auto epoch=perf::state().epoch.load();
    perf::timing(perf::RaceCalls,10000,7000,epoch);
    v=perf::snapshot();assert(v[264]==1&&v[265]==10000&&v[266]==7000);
    perf::timing(perf::RaceCalls,10000,7000,epoch-1);assert(perf::snapshot()[264]==1);
    {perf::Scope scope(perf::RaceCalls);perf::active(false);perf::active(true);}
    assert(perf::snapshot()[264]==1); // A scope across lifecycle changes is discarded.
    {perf::Scope scope(perf::RaceCalls);for(volatile int i=0;i<10000;++i){}}
    v=perf::snapshot();assert(v[264]==2&&v[265]>10000&&v[266]>=7000);
    perf::gameCycleBegin();for(volatile int i=0;i<10000;++i){}perf::gameCycleEnd();
    assert(perf::snapshot()[perf::GameCycleCalls]==1);
    perf::gameCycleBegin();perf::active(false);perf::active(true);perf::gameCycleEnd();
    assert(perf::snapshot()[perf::GameCycleCalls]==1);
    std::array<uint64_t,13> counts{};counts[0]=5;counts[1]=2;counts[2]=3;counts[12]=1;
    perf::boundaries(counts,1000,900,perf::state().epoch.load());v=perf::snapshot();
    assert(v[285]==5&&v[286]==2&&v[287]==3&&v[297]==1&&v[298]==1000&&v[299]==900);
    assert(v.size()==308);
    perf::rendererConfig(true,false);perf::opaqueUsage(7,21,3);v=perf::snapshot();
    assert(v[303]==7&&v[304]==21&&v[305]==3&&v[306]==1&&v[307]==0);
    std::cout<<"PASS v3 shader counters and phases, boundary totals, lifecycle rejection, game cycles, disabled capture, intervals, counters and concurrent snapshots\n";
}
