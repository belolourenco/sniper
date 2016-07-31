extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() { 
  int i, n=nondet_int(), sn,j;

  assume(n>=0 && n<1000);
  j=10;
  sn=0;
  i=1;

  while(i<=n) {
    sn = sn + 2;
    if (i<j) {sn = sn + 2;} else {}
    j=j-1;
    i=i+1;
  }
  
  assert(sn==n*2 || sn == 0);
  
}
