extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int i,tmp;
 int a[80];
 int b[80];

 i=0;
 while(i<80) {
   a[i]=nondet_int();
   b[i]=nondet_int();
   i=i+1;
 }
 
 b[80-1]=0;
 i = 0;
 while (b[i] != 0) {
    assert(i>=0 && i<80);
    tmp=b[i];
    a[i]=tmp;
    i = i + 1;
  }
  
}
