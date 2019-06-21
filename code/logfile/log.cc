#include <stdio.h>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/SimpleLayout.hh>
#include <zmq.hpp>
#include <string>
#include <iostream>

#define LOGFILE "./test.txt"
std::string rpl;
int main()
{   
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect ("tcp://localhost:5555");

    /*Setting up Appender, layout and Category*/
    log4cpp::Appender *appender = new log4cpp::FileAppender("FileAppender",LOGFILE);
    log4cpp::Layout *layout = new log4cpp::SimpleLayout();
    log4cpp::Category& category = log4cpp::Category::getInstance("Category");

    appender->setLayout(layout);
    category.setAppender(appender);
    category.setPriority(log4cpp::Priority::INFO);

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
        zmq::message_t request (5);
        memcpy (request.data (), "Hello", 5);
        std::cout << "Sending Hello " << request_nbr << "..." << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
         
         std::cout << "Received request: [" << std::string(static_cast<char*>(request.data()), request.size())  << "]" << std::endl;
         //strcpy(rpl,std::string(static_cast<char*>(reply.data()), reply.size());
    // catagory.info(std::string(static_cast<char*>(reply.data())));
         category.notice(std::string(static_cast<char*>(reply.data())));
    }
  //catagory.info(rpl);
    //   catagory.notice(a );
    //   catagory.warn(a );
    /*The actual logging*/

    // category.info("This is for tracing the flow");

    // category.warn("This is to generate certain warnings");
}
// g++ -I/usr/local/include/log4cpp -L/usr/local/lib/ -llog4cpp -lpthread -lzmq log.cc -std=c++14 
// LD_LIBRARY_PATH=/usr/local/lib ./a.out
