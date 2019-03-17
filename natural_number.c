#include <malloc.h>
#include <stdio.h>
#include <natural_number.h>
#include <math.h>


struct number *init_number(void) {
  struct number *num=malloc(sizeof(struct number));
  num->next=num;
  num->prev=num;
  num->digital=0;
  return num;
}

void destroy_number(struct number *num) {
  struct number *current=num->next;

  while (current!=num) {
    current=current->next;
    free(current->prev);
  }
  free(num);
}



struct number *clean_number(struct number * x) {
  struct number *p=x;
  if ((x->next)->digital!=0) return x;
  if ((x->next)->next==x) return x;  /* don't remove 0  if it's the last one */
  p=x->next;
  x->next=p->next;
  (x->next)->prev=x;
  free(p);
  return clean_number(x);
}

struct number *number_from_long(long x) {
  struct number *res;
  long t=fabs(x);
  res=init_number();
  if (x<0) set_sign(res,-1);

  while (t>0) {
    append_head(res,t%10);
    t/=10;
  }
  return clean_number(res);
}

struct number *number_from_string(char * c) {
  struct number *res;
  int d, init=0, next_loop=0;
  
  res=init_number();
  
  for (int i=0;c[i]!='\0';++i) {
    switch (c[i]) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      d=c[i]-'0';
      append_tail(res,d);

    }
    if (init==0 && c[i]=='-') {
      set_sign(res,-1);
      init=1;
    }

  }
  return res;
}













struct number *set_sign(struct number *x, char sign) {
  x->digital=sign;
  return x;
}


int get_sign(struct number *x) {
  if ((x->digital) < 0) return -1;
  return 1;
}

struct number *append_tail (struct number *num, char x) {
  struct number * newnumber = malloc(sizeof(struct number));
  newnumber->prev=newnumber;
  newnumber->next=newnumber;
  newnumber->digital=x%10;

  newnumber->prev=num->prev;
  (newnumber->prev)->next=newnumber;
  num->prev=newnumber;
  newnumber->next=num;

  return num;
}

struct number *append_head (struct number *num, char x) {
  struct number *newnumber=append_tail(num->next,x);
  return num;
}


int compare_length(struct number *x, struct number *y) {
  struct number *cx, *cy;
  cx=x,cy=y;
  while (1) {
    cx=cx->next;
    cy=cy->next;

    if (cx==x) {
      if (cy==y) {
	return DIGITAL_LEN_EQ;
      }
      return DIGITAL_LEN_LT;
    } 
    if (cy==y) return DIGITAL_LEN_GT;
  }
}

int compare_abs(struct number *x, struct number *y) {
  int res;
  res=compare_length(clean_number(x),clean_number(y));
  if (res!=0) return res;
  
  struct number *cx=x->next, *cy=y->next;
  while (1) {

    if (cx==x)
      break;


    if ((cx->digital) < (cy->digital)) {
	return -1;
    }

    if ((cx->digital) > (cy->digital)) {
	return 1;
    }
    cx=cx->next, cy=cy->next;
  }
  return 0;
}

int compare_number(struct number *x, struct number *y) {
  int sx,sy;
  sx=get_sign(x);
  sy=get_sign(y);
  printf("%d,%d\n",sx,sy);
  if (sx > sy) return DIGITAL_GT;
  if (sx < sy) return DIGITAL_LT;

  return sx * compare_abs(x,y);
}




struct number *natural_add (struct number * x, struct number *y) {
  int factx,facty,factr;
  factx=get_sign(x);
  facty=get_sign(y);
  
  int dx,dy,dz,x_out,y_out, overflow_v,temp,sign;
  struct number *result=init_number();

  sign=compare_abs(x,y);
  set_sign(result,factx);

  if (sign == DIGITAL_LT) {
    set_sign(result,facty);
  }
  factr=get_sign(result);
  
  
  struct number *cx=x->prev,*cy=y->prev;
  overflow_v=0;
  while (1) {
    if (cx!=x) {
      dx=cx->digital;
      cx=cx->prev;
    } else {
      dx=0;
    }
    if (cy!=y) {
      dy=cy->digital;
      cy=cy->prev;
    } else {
      dy=0;
    }

    temp=dx*factx*factr+dy*facty*factr+overflow_v;
    
    dz=(temp+20)%10;
    overflow_v=(temp+20)/10-2;


    /* printf("%d,%d,%d,%d,%d\n",dx,dy,temp,dz,overflow_v); */
    result=append_head(result,dz);

    if (cx==x && cy==y) {
      if (overflow_v!=0) result=append_head(result,overflow_v);
      break;
    }
  }
  return clean_number(result);
}

struct number *natural_sub (struct number *x, struct number *y) {
  struct number *m_y=natural_scale(y,1), *res;
  set_sign(m_y,-1*get_sign(y));
  res=natural_add(x,m_y);
  destroy_number(m_y);
  return res;
}



struct number *create_zero(void) {
  struct number *zero=init_number();
  zero=append_head(zero,0);
  return zero;
}



struct number *natural_scale (struct number* num, char x) {
  struct number *result, *tmp;
  struct number *zero=create_zero();
  if (x==0) {
    return zero;
  }
  if (x==1) {
    result=natural_add(num,zero);
    destroy_number(zero);
    return result;
  }

  tmp=natural_scale(num,x-1);
  result=natural_add(num,tmp);
  destroy_number(tmp);
  destroy_number(zero);
  
  return result;
}



void write_down(struct number *num) {
  struct number *h, *c;
  h=c=num;

  if (get_sign(num)!=1) printf("-");
  
  for (c=h->next; c!=h;c=c->next) {
    printf("%d",c->digital);
  }
  printf("\n");
}


struct number *natural_mul (struct number* x, struct number * y) {

  if (compare_length(x,y) == DIGITAL_LEN_GT) return natural_mul(y,x);
  struct number *px, *res, *tmp, *tmp_scale;
  res=create_zero();
  int dx;
  for (px=x->next;px!=x;px=px->next) {
    append_tail(res,0);
    dx=px->digital;
    tmp_scale=natural_scale(y,dx);
    tmp=natural_add(res,tmp_scale);
    destroy_number(tmp_scale);
    destroy_number(res);
    res=tmp;
  }
  set_sign(res,get_sign(x)*get_sign(y));
  return res;
}

struct number *natural_div (struct number * x, struct number *y) {
  struct number *res, *divisor , *cx, *tmp_divisor, *abs_y ;
  int dz;
  
  divisor=init_number();
  res=init_number();
  abs_y=natural_scale(y,1);
  
  set_sign(abs_y,1);
  
  for (cx=x->next; cx != x; cx=cx->next) {
    
    dz=0;
    append_tail(divisor,cx->digital);
    
    while (compare_abs(divisor, abs_y) != DIGITAL_LT ) {
      dz++;
      tmp_divisor=natural_sub(divisor,abs_y);
      destroy_number(divisor);
      divisor=tmp_divisor;
    }
    append_tail(res,dz);
  }
  destroy_number(divisor); 
  set_sign(res,get_sign(x)*get_sign(y));
  return clean_number(res);
}

struct number *natural_remain (struct number * x, struct number *y) {
  struct number *divisor , *cx, *tmp_divisor, *abs_y ;
  int dz;
  
  divisor=init_number();
  abs_y=natural_scale(y,1);
  
  set_sign(abs_y,1);
  
  for (cx=x->next; cx != x; cx=cx->next) {
    dz=0;
    append_tail(divisor,cx->digital);
    while (compare_abs(divisor, abs_y) != DIGITAL_LT ) {
      tmp_divisor=natural_sub(divisor,abs_y);
      destroy_number(divisor);
      divisor=tmp_divisor;
    }
  }
  
  set_sign(divisor,get_sign(x)*get_sign(y));
  return clean_number(divisor);
}






#ifdef NATURAL_TEST

int main() {
  struct number *x,*y;
  x=init_number();
  set_sign(x,1);
  append_head(x,1);
  append_head(x,2);
  append_head(x,3);
  append_head(x,4);
  append_head(x,5);
  append_head(x,6);
  y=init_number();

  set_sign(y,-1);
  append_head(y,1);
  append_head(y,1);


  /* struct number *z; */
  /* z=create_zero(); */
  /* append_head(z,1); */

  /* write_down(z); */
  /* write_down(x); */
  /* write_down(y); */

  write_down(natural_div(x,y));
  write_down(natural_remain(x,y));

  
  struct number *t1, *t2;
  t1=init_number();
  t2=init_number();

  append_head(t1,0);
  append_head(t1,6);

  append_head(t2,1);
  append_head(t2,1);

  write_down(t1);
  write_down(t2);


  struct number *a=number_from_long(123456);
  struct number *b=number_from_long(-123456);
  write_down(a);
  write_down(b);
  struct number *c=number_from_string("123456");
  struct number *d=number_from_string("-123456");
  struct number *e=number_from_string("-123a4 5b 6 -");

  write_down(c);
  write_down(d);
  write_down(e);


  printf("%d\n",compare_number(c,e));
  printf("%d\n",compare_number(e,c));
  printf("%d\n",compare_number(c,x));
  write_down(a);
  write_down(c);
  /* fab calculation */
  /* 
  struct number *one=init_number();
  append_head(one,1);
  struct number *c=natural_scale(one,1);
  struct number *fab=natural_scale(one,1);

  while (1) {
    c=natural_add(one,c);
    fab=natural_mul(fab,c);
    printf("current=");
    write_down(c);
    printf("fab=");
    write_down(fab);
  }
  */
}

#endif
