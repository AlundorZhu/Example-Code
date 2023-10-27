paint.out: main.o canvas.o command.o input_validation.o 
	gcc -g -Wall -Werror -o paint.out main.o canvas.o input_validation.o command.o

main.o: main.c canvas.h command.h input_validation.h
	gcc -g -Wall -Werror -c main.c

input_validation.o: input_validation.c canvas.h input_validation.h 
	gcc -g -Wall -Werror -c input_validation.c
	
command.o: command.c canvas.h command.h
	gcc -g -Wall -Werror -c command.c
	
canvas.o: canvas.c canvas.h
	gcc -g -Wall -Werror -c canvas.c

clean:
	rm -f *.o *.out