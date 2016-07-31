extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int ans;

int fib(int n){
 int  i, Fnew, Fold, temp;

 Fnew = 1;  
 Fold = 0;
 i = 2;
 while( i <= n ) {
  temp = Fnew;
  Fnew = Fnew + Fold;
  Fold = temp;
  i=i+1;
 }
 ans = Fnew;
 assert(i == n+1);
  return Fnew;
 
}
    
void f()
{
  int a = nondet_int();

  assume(a == 30);
  fib(a);
  
  assert(ans==832040);
  
}
