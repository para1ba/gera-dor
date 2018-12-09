FLEX=flex
BISON=bison
CC=gcc
CFLAGS=
LIBS=

PROGRAMA = regalloc
LEXICO = lexico.l
SINTATICO = sintatico.y

$(PROGRAMA): $(LEXICO) $(SINTATICO)
	$(FLEX) $(LEXICO)
	$(BISON) -d $(SINTATICO) -r states
	$(CC) -c *.c -g -I.
	$(CC) *.o -o $(PROGRAMA)

clean:
	rm -f *.yy.c
	rm -f *.tab.c
	rm -f *.tab.h
	rm -f *.output
	rm -f *.o
	rm -f regalloc
