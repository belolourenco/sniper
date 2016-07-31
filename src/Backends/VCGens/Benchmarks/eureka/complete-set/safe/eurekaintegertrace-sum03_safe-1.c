extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() { 
  int sn;
  int loop1, n1;
  int x;
  int n = nondet_int();

  assume(n > 0 && n <= 1000);
  sn=0;
  n1=nondet_int();
  loop1=nondet_int();
  x=0;
  while(x<=n){
    sn = sn + 2;
    x=x+1;
    assert(sn==x*2 || sn == 0);
    
  }
  
}
