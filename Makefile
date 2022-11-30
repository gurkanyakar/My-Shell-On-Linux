all:
	gcc myshell.c -o myshell
	gcc writef.c -o writef
	gcc execx.c -o execx

clean:
	rm myshell
	rm writef
	rm execx