
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();   

void f(){
  int i,pvlen = nondet_int();
  int tmp___1 = nondet_int();
  int k = 0;
  int n = nondet_int();

  i = 0;

  while ( nondet_int() )
    i = i + 1;
  if (i > pvlen) {
    pvlen = i;
  } else {

  }
  i = 0;

  while ( nondet_int() ) {
    tmp___1 = i;
    i = i + 1;
    k = k +1;
  }
  while ( nondet_int() );

  int j = 0;
  n = i;
  while (j < k) {

    assert(k >= 0);
    k = k -1;
    i = i - 1;
    j = j + 1;
  }
  return;
}
