
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();


void f() {
  int n0=nondet_int(), n1=nondet_int();
  int i = 0;
  int k = 0;

  while( i < 20*n0 ) {
    i++;
    k++;
  }
  i = 0;
  while( i < 6*n1+128 ) {
    i++;
    k++;
  }
  i = 0;
  while( i < 6*n1+128 ) {
    i++;
    k--;
  }
  i = 0;
  while( i < 20*n0 ) {
    assert(k > 0);
    i++;
    k--;
  }
  return;
}
