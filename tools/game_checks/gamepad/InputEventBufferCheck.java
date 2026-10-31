package dev.nfs3hp.port;
public class InputEventBufferCheck {
 static void check(boolean x){if(!x)throw new AssertionError();}
 public static void main(String[] args)throws Exception{
  InputEventBuffer b=new InputEventBuffer();check(b.version()==0);b.add(7,"a\nb\rc");
  check(b.snapshot().contains("a\\nb\\rc"));
  for(int i=0;i<600;i++)b.add(i,"event");check(b.snapshot().contains("dropped=89"));check(b.snapshot().split("\n").length==514);
  b.add(9,"x".repeat(10000));check(b.snapshot().length()<20000);
  Thread w=new Thread(()->{for(int i=0;i<1000;i++)b.add(i,"state");});w.start();
  for(int i=0;i<500;i++)check(b.snapshot().startsWith("version="));w.join();check(b.version()==1602);
  System.out.println("PASS Java input buffer: line escaping, bounded history/records, sequence and concurrent append/copy");
 }
}
