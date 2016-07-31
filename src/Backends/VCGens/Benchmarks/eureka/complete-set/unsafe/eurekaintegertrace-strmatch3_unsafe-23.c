extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

int s[23];
int p[3];

void f () {
  int i, j, l, found;

 i=0;
 while(i<23) {
   s[i]=nondet_int();
   i=i+1;
 }
 
 i=0;
 while(i<3) {
   p[i]=nondet_int();
   i=i+1;
 }
 

  i=0;
  found=0;
  int AUX = i<23 && found==0;
  while(AUX) {
    j=0;
    l=i;
    int AUX2 = j<3 && s[l]==p[j];
    while(AUX2) {
      assert(l>=0 && l<23);
      j=j+1;
      l=l+1;
      AUX2 = j<3 && s[l]==p[j];
      
    }
    
    if(j==3) {
      found=1;
    }
    
    i=i+1;
    AUX = i<23 && found==0;
  }
  
  if (found==1)
    { assert(s[i+1]==p[2]); } else {}
  
}
