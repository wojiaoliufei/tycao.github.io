.PHONY: http

CXX = g++

EXEC_HTTP = server_http

SOURCE_HTTP = main.cpp

# 开启编译器O3优化，pthread启用多线程
LDFLAGS_COMMON = -std=c++11 -O3 -lpthread -lboost_system

LPATH_COMMON = -I/home/zogy/boostbuild

LLIB_COMMON = -L/home/zogy/boostlib/stage/lib/lib

http:
	$(CXX) $(SOURCE_HTTP) $(LDFLAGS_COMMON) $(LPATH_COMMON) $(LLIB_COMMON) -o $(EXEC_HTTP)

clean:
	rm -f $(EXEC_HTTP) *.o

