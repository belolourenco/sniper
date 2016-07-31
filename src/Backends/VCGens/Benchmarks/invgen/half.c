
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int f() {
  int n=nondet_int(),i=nondet_int(),k=nondet_int();

  assume(n>=0);
  k = n;
  i = 0;
  while( i < n ) {
    k--;
    i = i + 2;
  }

  int j = 0;
 
  while( j < n/2 ) {
    assert(k > 0);
    k--;
    j++;
  }
  return 0;
}
