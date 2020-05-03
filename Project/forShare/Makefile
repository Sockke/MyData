all:./bin/srv ./bin/upload
./bin/srv:./test/main.cpp ./src/myevent.cpp ./src/tcpsocket.cpp ./src/server.cpp
	g++ -std=c++11 $^ -o $@ -lpthread -lboost_system -lboost_filesystem -lboost_thread -levent
./bin/upload:./src/upload.cpp    
	g++ -std=c++11 $^ -o $@ -lboost_system -lboost_filesystem -lboost_thread    

