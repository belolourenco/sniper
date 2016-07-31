extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int i,tmp;
 int a[90];
 int b[90];

 i=0;
 while(i<90) {
   a[i]=nondet_int();
   b[i]=nondet_int();
   i=i+1;
 }
 
 b[90-1]=0;
 i = 0;
 while (b[i] != 0) {
    assert(i>=0 && i<90);
    tmp=b[i];
    a[i]=tmp;
    i = i + 1;
  }
  
}
