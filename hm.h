
#define DIGITAL_LEN_EQ 0
#define DIGITAL_LEN_LT -1
#define DIGITAL_LEN_GT 1

#define DIGITAL_EQ 0
#define DIGITAL_LT -1
#define DIGITAL_GT 1





#define list_empty(num) \
  ((num)->prev == num)

struct number {
  struct number *next;
  struct number *prev;
  int digital;
};


struct number *init_number(void);
void destroy_number(struct number *);
struct number *clean_number(struct number *); /* use to remove leading 0 */

struct number *number_from_long(long );
struct number *number_from_string(char *);







struct number *set_sign(struct number *num, int sign); /* negative one means this number is negative */ 
int get_sign (struct number *num);

struct number *append_tail(struct number *, int);
struct number *append_head(struct number *, int);

int compare_abs (struct number *, struct number *);
int compare_length (struct number *, struct number *);
int compare_number(struct number *, struct number *);

struct number *do_add (struct number*, struct number*);
struct number *do_sub (struct number*, struct number*);


struct number *create_zero(void) ;
struct number *do_scale (struct number*, int);

struct number *do_mul (struct number*, struct number *);

struct number *do_div (struct number*, struct number *);
struct number *do_remain (struct number*, struct number *);





void write_down(struct number *);
