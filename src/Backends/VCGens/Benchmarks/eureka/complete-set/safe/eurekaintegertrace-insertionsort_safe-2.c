extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int a[2];
  int i,j,temp,AUX;
  
  i = 0;
  while(i<2) {
    a[i] = nondet_int();
      i = i+1;
  }
  j = 1;
  while(j<2){
    temp = a[j];
    i = j-1;
    AUX = i>=0 && a[i]>temp;
    while(AUX){
      a[i+1] = a[i];
      i = i-1;
    AUX = i>=0 && a[i]>temp;
    }
    a[i+1]=temp;
    j=j+1;
  }
  assert(a[0]<=a[0+1]);

 
}
