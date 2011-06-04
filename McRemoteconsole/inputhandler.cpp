//
//  inputhandler.cpp
//  McRemoteconsole
//
//  Created by Tom Alexander Träskbäck on 6/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "inputhandler.h"
#include <iostream>

inputhandler::inputhandler() 
{
 quit=false;
}

void inputhandler::start(boost::process::postream *sout)
{
 inputhandler::m_Thread = boost::thread(&inputhandler::processQueue, this, sout);
}

void inputhandler::join()
{
 inputhandler::m_Thread.join();
}

void inputhandler::interupt()
{
 inputhandler::m_Thread.interrupt();
}

void inputhandler::processQueue(boost::process::postream *sout)
{
 std::string Line;
 while(!quit)
 {
  std::getline(std::cin,Line);
  if(Line=="/quit")
  {
   quit=true;
   *sout<<"stop" << std::endl;
  }else if(Line=="stop")
  {
   quit=true;
   *sout<<Line << std::endl;
   return;
  }else
  {
   *sout<<Line << std::endl;
  }
 }
}