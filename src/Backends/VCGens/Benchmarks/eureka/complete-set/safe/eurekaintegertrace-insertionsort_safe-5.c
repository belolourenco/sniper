extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int a[5];
  int i,j,temp,AUX;
  
  i = 0;
  while(i<5) {
    a[i] = nondet_int();
      i = i+1;
  }
  j = 1;
  while(j<5){
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
  assert(a[0]<=a[0+1] && a[1]<=a[1+1] && a[2]<=a[2+1] && a[3]<=a[3+1]);

}
