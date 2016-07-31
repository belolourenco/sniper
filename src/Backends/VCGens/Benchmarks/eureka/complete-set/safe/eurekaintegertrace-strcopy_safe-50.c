extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int i,tmp;
 int a[50];
 int b[50];

 i=0;
 while(i<50) {
   a[i]=nondet_int();
   b[i]=nondet_int();
   i=i+1;
 }
 
 b[50-1]=0;
 i = 0;
 while (b[i] != 0) {
    assert(i>=0 && i<50);
    tmp=b[i];
    a[i]=tmp;
    i = i + 1;
  }
  
}
