//
//  ouputhandler.h
//  McRemoteconsole
//
//  Created by Tom Alexander Träskbäck on 6/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __McRemoteconsole__ouputhandler__
#define __McRemoteconsole__ouputhandler__

#include <boost/thread.hpp>
#include <boost/asio.hpp> 
#include <boost/process.hpp>
#include <boost/array.hpp> 
#include <boost/bind.hpp>

namespace ba = boost::asio; 
class outputhandler
{
public:
 
 outputhandler() ;
 
 void start(boost::process::pistream *sin); 
 void join();
 void interupt();
 
 void processQueue(boost::process::pistream *sin);
 
private:
 boost::thread m_Thread;
};

#endif
