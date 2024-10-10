
OBJS = tokenizer.o history.o uimain.o

CFLAGS = -g -O3

all: token

token: $(OBJS)
		cc -o token $(CFLAGS) $(OBJS)

tokenizer.o: tokenizer.c tokenizer.h
		cc -c $(CFLAGS) tokenizer.c

history.o: history.c history.h
		cc -c $(CFLAGS) history.c

main.o: main.c tokenizer.h history.h
		cc -c $(CFLAGS) main.c

clean:
		rm -f *.o token

run: token
		./token
