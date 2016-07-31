
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int n=nondet_int(), m=nondet_int();
  int i = 0;
  int k = 0;

  while( i < n ) {
    i++;
    k++;
  }
  i = 0;
  while( i < m ) {
    i++;
    k++;
  }
  i = 0;
  while( i < m ) {
    i++;
    k--;
  }
  i = 0;
  while( i < n ) {
    assert(k > 0);
    i++;
    k--;
  }
  return;
}
