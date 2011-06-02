//
//  main.cpp
//  McRemoteconsole
//
//  Created by Tom Alexander Träskbäck on 5/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#if defined(__CYGWIN__) 
#  define _WIN32_WINNT 0x0501 
#  define __USE_W32_SOCKETS 
#  undef BOOST_POSIX_API 
#  define BOOST_WINDOWS_API 
#endif 
#include <boost/asio.hpp> 
#define BOOST_PROCESS_WINDOWS_USE_NAMED_PIPE 
#include <boost/process.hpp> 
#include <boost/array.hpp> 
#include <boost/bind.hpp> 
#include <string> 
#include <vector> 

namespace bp = ::boost::process; 
namespace ba = ::boost::asio; 

using namespace std;

ba::io_service io_service; 
boost::array<char, 4096> buffer; 

#if defined(BOOST_POSIX_API) 
ba::posix::stream_descriptor in(io_service); 
#elif defined(BOOST_WINDOWS_API) 
ba::windows::stream_handle in(io_service); 
#else 
#  error "Unsupported platform." 
#endif 

bp::child start_child() 
{ 
 std::string exec = "/usr/bin/java"; 
 
 std::vector<std::string> args;
 args.push_back("java");
 args.push_back("-jar");
 args.push_back("craftbukkit.jar");
 args.push_back("--nojline");
 
 bp::context ctx;
 ctx.environment = bp::self::get_environment(); 
 ctx.stdout_behavior = bp::capture_stream(); 
 ctx.stderr_behavior = bp::capture_stream(); 
 ctx.stdin_behavior = bp::capture_stream();
 return bp::launch(exec, args, ctx); 
} 

void end_read(const boost::system::error_code &ec, std::size_t bytes_transferred); 

void begin_read() 
{ 
 in.async_read_some(boost::asio::buffer(buffer), 
                    boost::bind(&end_read, ba::placeholders::error, ba::placeholders::bytes_transferred)); 
} 

void end_read(const boost::system::error_code &ec, std::size_t bytes_transferred) 
{ 
 if (!ec) 
 { 
  std::cout << std::string(buffer.data(), bytes_transferred) << std::flush; 
  begin_read(); 
 } 
} 

int main() 
{ 
 bp::child c = start_child(); 
 
 bp::pistream &is = c.get_stderr();
 bp::postream &out = c.get_stdin();
 in.assign(is.handle().release()); 
 begin_read();
 io_service.run();
 c.wait(); 
} 