#include <lib/input_trace.h>
#include <cassert>
#include <algorithm>
#include <thread>
#include <iostream>
int main(){
 win32::InputTrace t;t.note(0,"disabled");assert(t.snapshot(0).empty());
 t.active(true);assert(t.state(1,"slot0","a","raw=1"));assert(!t.state(2,"slot0","a","duplicate"));
 auto report=t.snapshot(0);assert(report.find("raw=1")!=std::string::npos&&report.find("duplicate")==std::string::npos);
 assert(t.snapshot(1).empty());t.note(3,"newline\nUTF8 \xf0\x9f\x98\x80");report=t.snapshot(0);
 assert(report.find("newline\\nUTF8 \\xf0\\x9f\\x98\\x80")!=std::string::npos);
 for(unsigned char c:report)assert(c<128); // Safe for NewStringUTF regardless of controller name.
 for(int i=0;i<700;i++)t.note(i,"bounded");report=t.snapshot(0);assert(report.find("dropped=190")!=std::string::npos);
 assert(std::count(report.begin(),report.end(),'\n')==514);
 t.active(false);report=t.snapshot(0);t.note(999,"disabled again");assert(t.snapshot(0)==report);
 t.active(true);assert(t.snapshot(0).empty());assert(t.state(1,"slot0","a","new session identity"));
 std::thread writer([&](){for(int i=0;i<10000;i++)t.state(i,"slot0",std::to_string(i),"state");});
 std::thread reader([&](){for(int i=0;i<1000;i++)t.snapshot(0);});writer.join();reader.join();
 std::cout<<"PASS native trace: disabled no-op, duplicate filtering, bounded ring, reset identity, escaped UTF8, concurrent record/copy\n";
}
