extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int i,tmp;
 int a[10];
 int b[10];

 i=0;
 while(i<10) {
   a[i]=nondet_int();
   b[i]=nondet_int();
   i=i+1;
 }
 
 i = 0;
 while (b[i] != 0) {
    assert(i>=0 && i<10);
    tmp=b[i];
    a[i]=tmp;
    i = i + 1;
  }
  
}
