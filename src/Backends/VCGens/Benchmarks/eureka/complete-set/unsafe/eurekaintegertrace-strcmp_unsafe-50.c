extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int s1[50];
 int s2[50];
 int i,result;

 i=0;
 int AUX = s1[i] == s2[i] && s1[i] != 0;
 while (AUX) {
  i=i+1;
  assert(i>=0 && i<50);
  AUX = s1[i] == s2[i] && s1[i] != 0;
 }
 
 result = s1[i] - s2[i];
}
