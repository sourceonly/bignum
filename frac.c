#include <natural_number.h>

int main() {
  struct number *c,*frac,*one,*zero,*tmp;
  one=init_number();
  append_tail(one,1);
  zero=create_zero();
  c=natural_add(one,zero);
  frac=c;
  while(1) {

    tmp=natural_mul(c,frac);
    frac=tmp;
    tmp=natural_add(one,c);
    c=tmp;
    write_down(c);
    write_down(frac);
  }
}
