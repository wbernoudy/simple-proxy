CFLAGS = -lpthread -Wall
LIB = 

all:
	make clean
	make myproxy

myproxy: 
	g++ -o myproxy myproxy.cpp ${CFLAGS} ${LIB} -I.

	
clean:
	rm -f myproxy