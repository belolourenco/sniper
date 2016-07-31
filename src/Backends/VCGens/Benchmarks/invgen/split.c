
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int k = nondet_int();
  assume(k == 100);
  int b=nondet_int();
  int i=nondet_int();
  int j=nondet_int();
  int n=nondet_int();
  int AUXVARIABLE = nondet_int();
  assume(AUXVARIABLE == 200);
  i = j;
  for( n = 0 ; n < AUXVARIABLE ; n++ ) {    // replaced from for( n = 0 ; n < 2*k ; n++ ) {   
    if(b) {
      i++;
    } else {
      j++;
    }
    b = !b;
  }
  assert(i == j);
}
