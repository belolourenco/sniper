extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int s1[100];
 int s2[100];
 int i,result;

 i=0;
 while(i<100) {
   s1[i]=nondet_int();
   s2[i]=nondet_int();
   i=i+1;
 }
 
 s1[100-1] = 0;
 i=0;
 int AUX = s1[i] == s2[i] && s1[i] != 0;
 while (AUX) {
  i=i+1;
  assert(i>=0 && i<100);
  AUX = s1[i] == s2[i] && s1[i] != 0;
 }
 
 result = s1[i] - s2[i];
}
