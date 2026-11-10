# MAKEFILE

preprocessor: main.o header.o comment.o marco_replacement.o
	cc main.o header.o comment.o marco_replacement.o -o preprocessor

main.o: main.c
	cc -c main.c

header.o: header.c
	cc -c header.c

comment.o: comment.c
	cc -c comment.c

marco_replacement.o: marco_replacement.c
	cc -c marco_replacement.c

clear:
	@echo "cleaning up"
	@rm -v *.o
