
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int i=nondet_int(),k=nondet_int(),n=nondet_int(),l=nondet_int();

  assume(l>0);
  for (k=1;k<n;k++){
    for (i=l;i<n;i++){  
      assert(1<=i);
    }
    if(nondet_int())
      l = l + 1;
  }
 }
