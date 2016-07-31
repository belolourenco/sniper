
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f() {
  int n0=nondet_int(), n1=nondet_int();

  int i0 = 0;
  int k = 0;
  while( i0 < n0 ) {
    i0++;
    k++;
  }
  int i1 = 0;
  while( i1 < n1 ) {
    i0--;
    i1++;
    k++;
  }
  int j1 = 0;
  while( j1 < n1 ) {
    assert(!(k <= 0));
    j1++;//i0++;i1++;
    k--;
  }
  int j0 = 0;
  while( j0 < n0 ) {
    assert(!(k <= 0));
    j0++;//j1++;i0++;i1++;
    k--;
  }

  //  assert( n0 + n1 <= i0 );
  return 0;
}
