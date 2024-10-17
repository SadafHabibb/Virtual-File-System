VFS.out: main.o vfs.o inode.o queue.o vector.o
	g++ main.o vfs.o inode.o queue.o vector.o -o VFS.out

main.o: main.cpp vfs.hpp
	g++ -c main.cpp

inode.o: inode.cpp inode.hpp vector.hpp
	g++ -c inode.cpp

queue.o: queue.cpp queue.hpp
	g++ -c queue.cpp

vector.o: vector.cpp vector.hpp
	g++ -c vector.cpp

vfs.o: vfs.cpp vfs.hpp inode.hpp queue.hpp
	g++ -c vfs.cpp

clean:
	rm main.o inode.o queue.o vector.o vfs.o VFS.out









