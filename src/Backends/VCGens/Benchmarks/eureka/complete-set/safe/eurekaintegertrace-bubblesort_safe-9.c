extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
 int i,j,temp;
 int a[9];

 i=0;
 while(i<9) {
   a[i]=nondet_int();
   i=i+1;
 }
 j=0;
 while(j<9-1) {
   i=0;
   while(i<9-j-1) {
     temp = a[i+1];
     if (a[i] > temp){ 
	 a[i+1] = a[i];
	 a[i] = temp;
     }
     i=i+1;
   }
   j=j+1;
 }
 assert(a[0]<=a[0+1] && a[1]<=a[1+1] && a[2]<=a[2+1] && a[3]<=a[3+1] && a[4]<=a[4+1] && a[5]<=a[5+1] && a[6]<=a[6+1] && a[7]<=a[7+1]);

 
}
