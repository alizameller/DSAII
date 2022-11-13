dijkstras.exe: dijkstras.o heap.o hash.o
	g++ -o dijkstras.exe dijkstras.o heap.o hash.o

dijkstras.o: dijkstras.cpp
	g++ -c dijkstras.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o dijkstrasDebug.exe dijkstras.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups