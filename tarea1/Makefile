TARGET = driver
DYNAMIC_LIB = libucsp.so
STATIC_LIB = libucsp.a

CFLAGS = -Wall -fPIC
LDFLAGS = -L.

OBJS = ucsp.o

all: dynamic static

dynamic: $(OBJS)
	gcc $(CFLAGS) -c $(TARGET).c
	gcc -shared -o $(DYNAMIC_LIB) $(OBJS)
	gcc $(TARGET).c $(LDFLAGS) -lucsp -o main.dynamic.exe

static: $(OBJS)
	ar rcs $(STATIC_LIB) $(OBJS)
	gcc $(TARGET).c $(LDFLAGS) $(STATIC_LIB) -o main.static.exe

$(OBJS): ucsp.c ucsp.h
	gcc $(CFLAGS) -c ucsp.c

clean:
	rm -f *.o *.so *.a main.dynamic.exe main.static.exe

run-dynamic: dynamic
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH && ./main.dynamic.exe

run-static: static
	./main.static.exe
