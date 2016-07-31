
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int n = nondet_int();
  int k = 0;
  int i = 0;
  while( i < n ) {
	 i++;
	 k++;
  }
  int j = n;
  while( j > 0 ) {
	 assert(k > 0);
	 j--;
	 k--;
  }
}
