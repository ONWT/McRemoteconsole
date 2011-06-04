//
//  ouputhandler.cpp
//  McRemoteconsole
//
//  Created by Tom Alexander Träskbäck on 6/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ouputhandler.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

outputhandler::outputhandler() 
{
 
}

void outputhandler::start(boost::process::pistream *sin)
{
 outputhandler::m_Thread = boost::thread(&outputhandler::processQueue, this, sin);
}

void outputhandler::join()
{
 outputhandler::m_Thread.join();
}

void outputhandler::interupt()
{
 outputhandler::m_Thread.interrupt();
}

void outputhandler::processQueue(boost::process::pistream *sin)
{
 std::string line; 
 while (std::getline(*sin, line))
 {
  if(line.find("Stopping the server..")!= std::string::npos)
  {
   //Bale out the server is stopping
   //return;
  }
  std::cout << line << std::endl;
 }
}
