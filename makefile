all:
	gcc -Wall -Iapp -c app/rtcc.c -o rtcc.o
	gcc -Wall -Iapp -c app/queue.c -o queue.o
	gcc -Wall -Iapp -c app/scheduler.c -o scheduler.o
	gcc -Wall -Iapp -c app/main.c -o main.o
	gcc main.o rtcc.o queue.o scheduler.o  -o main.exe
	./main.exe
	
clean:
	rm *.exe *.o 

#---Generates project documentation with doxygen---------------------------------------------------
#DOXYGEN = "C:/Program Files/doxygen/bin"
#DOXYGEN = "C:\Program Files\doxygen\bin"

#docs :
#	$(DOXYGEN) .doxyfile
#	microsoft-edge Build/doxygen/html/index.html