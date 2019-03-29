

INCLUDE=-I.
LIB=-L.
LD_FLAGS=-lnatural

all: fib frac gcd

natural_number:
	cc $(INCLUDE) -c natural_number.c
lib: natural_number
	cc $(INCLUDE) -fPIC --shared -o libnatural.so  natural_number.o

fib:	lib
	cc $(LIB) $(LD_FLAGS) $(INCLUDE) -o fib fib.c


frac:	lib
	cc $(LIB) $(LD_FLAGS) $(INCLUDE) -o frac frac.c

gcd:	lib
	cc $(LIB) $(LD_FLAGS) $(INCLUDE) -o gcd gcd.c


.PHONY:
clean:
	-rm -rf *.so *.o fib frac gcd *~ a.out fab
