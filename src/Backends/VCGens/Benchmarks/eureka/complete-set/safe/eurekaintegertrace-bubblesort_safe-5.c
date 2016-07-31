extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int i,j,temp;
 int a[5];

 i=0;
 while(i<5) {
   a[i]=nondet_int();
   i=i+1;
 }
 j=0;
 while(j<5-1) {
   i=0;
   while(i<5-j-1) {
     temp = a[i+1];
     if (a[i] > temp){ 
	 a[i+1] = a[i];
	 a[i] = temp;
     }
     i=i+1;
   }
   j=j+1;
 }
 assert(a[0]<=a[0+1] && a[1]<=a[1+1] && a[2]<=a[2+1] && a[3]<=a[3+1]);

 
}
