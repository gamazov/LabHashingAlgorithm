all:
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D HASH1
	./a.out ../test/100.txt
	./a.out ../test/500.txt
	./a.out ../test/1000.txt
	./a.out ../test/5000.txt
	./a.out ../test/10000.txt
	./a.out ../test/50000.txt
	./a.out ../test/100000.txt
	./a.out ../test/500000.txt
	./a.out ../test/1000000.txt
	./a.out ../test/1500000.txt
	./a.out ../test/2000000.txt
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D HASH2
	./a.out ../test/100.txt
	./a.out ../test/500.txt
	./a.out ../test/1000.txt
	./a.out ../test/5000.txt
	./a.out ../test/10000.txt
	./a.out ../test/50000.txt
	./a.out ../test/100000.txt
	./a.out ../test/500000.txt
	./a.out ../test/1000000.txt
	./a.out ../test/1500000.txt
	./a.out ../test/2000000.txt

hash1:
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D HASH1
hash2:
	g++ -std=c++11 -Wall -Werror -Wextra main.cpp -D HASH2
clean:
	rm -f a.out