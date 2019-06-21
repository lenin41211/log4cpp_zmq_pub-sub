#include "zhelpers.hpp"

int main () {
    //  Prepare our context and publisher
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5563");

    while (1) {
        //  Write two messages, each with an envelope and content
        s_sendmore (publisher, "A");
        s_send (publisher, "AAAA We don't want to see this");
        s_sendmore (publisher, "B");
        s_send (publisher, "BBBBB We would like to see this");
        sleep (1);
    }
    return 0;
}

// g++ -I/usr/include/ -L/usr/include -lzmq pub.cpp -std=c++14
