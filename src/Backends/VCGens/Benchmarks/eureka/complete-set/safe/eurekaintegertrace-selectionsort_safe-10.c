extern void assert(int x);
extern void assume(int x);
extern int nondet_int();

void f() {
  int a[10];
  int i,j,temp,min;

    i = 0;
    while(i<10) {
      a[i] = nondet_int();
      i = i+1;
    }
    j = 0;
    while(j<10-1){
	min = j;
	temp = a[min];
	i = j+1;
	while(i<10){
	  if(a[i]<temp){
	    min = i;
	    temp = a[min];
	  } else {  }
	  i = i+1;
	}
	temp = a[j]; 
	a[j] = a[min];	
	a[min] = temp;
	j=j+1;
    }
    assert(a[0]<=a[0+1] && a[1]<=a[1+1] && a[2]<=a[2+1] && a[3]<=a[3+1] && a[4]<=a[4+1] && a[5]<=a[5+1] && a[6]<=a[6+1] && a[7]<=a[7+1] && a[8]<=a[8+1]);

 
}
