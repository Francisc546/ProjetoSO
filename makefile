all: simulador monitor

simulador: simulador.o sockets.o util.o tempo.o
	gcc -g -o simulador sockets.o simulador.o util.o tempo.o -lpthread  
	
monitor: monitor.o sockets.o util.o tempo.o
	gcc -g -o monitor sockets.o monitor.o util.o tempo.o -lpthread
	
sockets.o: library.h sockets.c
	gcc -c -g sockets.c
	
util.o: library.h util.c
	gcc -c -g util.c
	
monitor.o: library.h monitor.c
	gcc -c -g monitor.c
	
simulador.o: library.h simulador.c
	gcc -c -g simulador.c
	
tempo.o : library.h tempo.c
	gcc -c -g tempo.c
	
Clean: 
	rm *.o simulador monitor
