
extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

// This is an iterative version of merge sort.
// It merges pairs of two consecutive lists one after another.
// After scanning the whole array to do the above job,
// it goes to the next stage. Variable k controls the size
// of lists to be merged. k doubles each time the main loop
// is executed.

void f(){ 
  int i=nondet_int(),n=nondet_int(),t=nondet_int(),k=nondet_int();
  int l=nondet_int(),r=nondet_int(),u=nondet_int(),j=nondet_int();
  int x=nondet_int(),y=nondet_int(),z=nondet_int();
  x=1;
  while (x<n) {
    z=1;
    while (z+x<=n) {
      y=z+x*2;
      if (y>n) y=n+1;
      l = z; r = z+x; u = y;
      i=l; j=r; k=l;
      int AUXVARIABLE = i<r && j<u;
      while (AUXVARIABLE) { 
	       if(nondet_int()) {
	         i++;
	       } 
	       else {
	         j++;
	       }
	       k++;
         AUXVARIABLE = i<r && j<u;
      }
      
      assert(k<=n);
      
      while (i<r) {
	       i++; 
	       k++;
      }
      while (j<u) { 
	       j++; 
         k++;
      }
      for (k=l; k<u; k++) { 
      }
      
      z=z+x*2;
    }
    x=x*2;
  }
}
