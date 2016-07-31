
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int n=nondet_int();
  int i = 0;
  int k = 0;
  while( i < n ) {
	i = i + 2;
	k++;
  }
  int j = 0;
  while( j < n ) {
    assert(k > 0);
	j = j + 2;
	k--;
  }
}
