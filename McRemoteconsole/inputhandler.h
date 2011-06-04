//
//  inputhandler.h
//  McRemoteconsole
//
//  Created by Tom Alexander Träskbäck on 6/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __McRemoteconsole__inputhandler__
#define __McRemoteconsole__inputhandler__

#include <boost/thread.hpp>
#include <boost/process.hpp>

class inputhandler
{
public:
 
 inputhandler() ;
 
 void start(boost::process::postream *sout); 
 void join();
 void interupt();
 
 void processQueue(boost::process::postream *sout);
 
private:
 boost::thread m_Thread;
 bool quit;
};


#endif
