extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int i,j,temp, AUX;
 int a[3];

 i=0;
 while(i<3) {
   a[i]=nondet_int();
   i=i+1;
 }
 j=0;
 while(j<3-1) {
   i=0;
   while(i<3-j-1) {
     temp = a[i+1];
     if (a[i] < temp){ 
	 a[i+1] = a[i];
	 a[i] = temp;
     }
     i=i+1;
   }
   j=j+1;
 }
 assert(a[0]<=a[0+1] && a[1]<=a[1+1]);

 
}
