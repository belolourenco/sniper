extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int a[10];

void f()
{
  int x=nondet_int(),i,k,j,tmp;

  assume(x==0);
  while (x<5) {
    j=a[0];
    i=0;
    while(i < 5) {
      k=10-1-i;
      tmp=a[k];
      a[k] = a[i];
      a[i]=tmp;
      i=i+1;
    } 
    
    assert(j==a[10-1]);
     
    i = nondet_int();
    assume(i==0);
    while(i < 10) {
      k=10-1-i;
      tmp=a[k];
      a[k] = a[i];
      a[i]=tmp;
      i=i+1;
    } 
    
   assert(j==a[0]);
    x=x+1;
    }

}
