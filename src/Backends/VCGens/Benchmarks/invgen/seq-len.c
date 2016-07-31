
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f() {
  int n0=nondet_int(), n1=nondet_int(),n2=nondet_int();
  int i = 0;
  int k = 0;

  while( i < n0 ) {
    i++;
    k++;
  }
  i = 0;
  while( i < n1 ) {
    i++;
    k++;
  }

  i = 0;
  while( i < n2 ) {
    i++;
    k++;
  }

  i = 0;
  while( i < n2 ) {
    i++;
    k--;
  }

  i = 0;
  while( i < n1 ) {
    i++;
    k--;
  }
  i = 0;
  while( i < n0 ) {
    assert(k > 0);
    i++;
    k--;
  }
  return 0;
}
