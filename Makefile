CC=cc

#CFLAGS=$(shell pkg-config --cflags opencv) 
#LIBS=$(shell pkg-config --libs opencv) 

OBJS= main.o  SubstChiffre.o
TARGET=main


SubstChiffre.o:	SubstChiffre.cpp
	$(CC) -c $<  -std=c++11 

main.o:	main.cpp
	$(CC) -c $<  -std=c++11	

main:	$(OBJS)
	$(CC) -o $@ $^ -L/usr/lib/x86_64-linux-gnu -ldl -lstdc++  -std=c++11 -lpthread $(LIBS)

clean:
	-rm -r -f   $(TARGET) *.o DOXYGENDOC  *.txt

doc:
	doxygen Doxyfile 


all:	$(TARGET)
	make clean  && make main
