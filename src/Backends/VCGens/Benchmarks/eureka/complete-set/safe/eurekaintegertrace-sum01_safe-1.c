extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() { 
  int i, n=nondet_int(), sn;
  
  assume(n>=0 && n<1000);
  
  sn=0;
  i=1;
  while (i<=n) {
    sn = sn + 2;
    i=i+1;
  }
  assert((sn>n+n-2 && sn<=n+n) || sn == 0);
  
}
