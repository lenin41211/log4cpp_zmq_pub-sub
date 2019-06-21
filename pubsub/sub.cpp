#include "zhelpers.hpp"
#include <stdio.h>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/SimpleLayout.hh>
#include <zmq.hpp>
#include <string>
#include <iostream>

#define LOGFILE "./test.csv"
std::string rpl;

int main () {
    //  Prepare our context and subscriber
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");

    /*Setting up Appender, layout and Category*/
    log4cpp::Appender *appender = new log4cpp::FileAppender("FileAppender",LOGFILE);
    log4cpp::Layout *layout = new log4cpp::SimpleLayout();
    log4cpp::Category& category = log4cpp::Category::getInstance("Category");

    appender->setLayout(layout);
    category.setAppender(appender);
    category.setPriority(log4cpp::Priority::INFO);

    subscriber.setsockopt( ZMQ_SUBSCRIBE, "B", 1);

    while (1) {

        //  Read envelope with address
        std::string address = s_recv (subscriber);
        //  Read message contents
        std::string contents = s_recv (subscriber);
	
          // category.notice(std::string(static_cast<char*>(contents));       
 category.notice(contents);     
 category.info(contents);    
 category.warn(contents);            
	// std::cout << "[" << address << "] " << contents << std::endl;
    }
    return 0;
}

// g++ -I/usr/include/ -L/usr/include  -lzmq sub.cpp -std=c++14
// g++ -I/usr/local/include/log4cpp -L/usr/local/lib/ -llog4cpp -lpthread -lzmq log.cc -std=c++14 
// LD_LIBRARY_PATH=/usr/local/lib ./a.out
