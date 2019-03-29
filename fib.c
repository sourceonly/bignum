#include <natural_number.h>

int main() {
  struct number *f1, *f2, *f3, *tmp;
  struct number *one=number_from_long(1);
  f1=one;
  f2=natural_add(f1,one);
  
  int i=0;
  while (i<100) {
    ++i;
    usleep(100);
    f3=natural_add(f1,f2);
    tmp=f1,f1=f2,f2=f3;
    destroy_number(tmp);
    write_down(f1);
  }
  destroy_number(f1);
  destroy_number(f2);
}
