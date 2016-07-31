extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int ans;

int fib(int n){
 int  i, Fnew, Fold, temp;

 Fnew = 1;  
 Fold = 1;
 i = 2;
 while( i <= n ) {
  temp = Fnew;
  Fnew = Fnew + Fold;
  Fold = temp;
  i=i+1;
 }
 ans = Fnew;
 return ans;
 
}
    
void f()
{
  int a;

  a = 30;
  fib(a);
  
  assert(ans==832040);
  
}
