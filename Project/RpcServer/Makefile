all: ./bin/srv ./bin/cli
./bin/srv: ./test/testServer.cpp ./src/* ./include/*.cc ./test/*.cc 
	g++ -g -std=c++11 $^ -o $@ -lprotobuf -lmuduo_net -lmuduo_base -lpthread -lzookeeper_mt ./third_party/tinyxml/libtinyxml.so
./bin/cli: ./test/testClient.cpp ./src/* ./include/*.cc ./test/*.cc
	g++ -std=c++11 $^ -o $@ -lprotobuf -lmuduo_net -lmuduo_base -lpthread -lzookeeper_mt ./third_party/tinyxml/libtinyxml.so

