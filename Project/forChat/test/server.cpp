#include "chatServer.hpp"
#include "chatService.hpp"
#include <signal.h>

void serverQuit(int signo) {
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("input error: ./chatServer ip port");
        return -1;
    }
    const char* ip = argv[1];
    unsigned short port = atoi(argv[2]);

    signal(SIGINT, serverQuit);

    EventLoop loop;
    InetAddress addr(ip, port);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();
    
    return 0;
}