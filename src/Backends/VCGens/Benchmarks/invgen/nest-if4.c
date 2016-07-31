
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int i=nondet_int(),k=nondet_int(),n=nondet_int(),l=nondet_int();

  assume(l>0);
  for (k=1;k<n;k++){
    if(nondet_int())
      for (i=l;i<n;i++)
	     assert(1<=i);
    for (i=l;i<n;i++);
  }

 }
