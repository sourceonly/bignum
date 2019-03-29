#include <natural_number.h>

int main() {
  struct number *c,*frac,*one,*zero,*tmp;
  one=init_number();
  append_tail(one,1);
  zero=create_zero();
  c=natural_add(one,zero);
  frac=natural_add(c,zero);
  
  destroy_number(zero);

  while(1) {
    tmp=natural_mul(c,frac);
    destroy_number(frac);
    frac=tmp;
    tmp=natural_add(one,c);
    destroy_number(c);
    c=tmp;
    write_down(c);
    write_down(frac);
  }
  
  destroy_number(one);
  destroy_number(c);
  destroy_number(frac);
}
