.PHONY: clean

INLCUDE=-I/usr/local/freetds/include/

LIB=-L/usr/local/freetds/lib/ \
	-lsybdb

run:
	g++ -std=c++11 ${INLCUDE} ${LIB} manager.cpp test.cpp -o test -lsybdb

clean:
	rm -f *.o test
