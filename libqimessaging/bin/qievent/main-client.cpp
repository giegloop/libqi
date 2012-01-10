/*
** main-client.cpp
** Login : <hcuche@hcuche-de>
** Started on  Tue Jan  3 13:52:00 2012 Herve Cuche
** $Id$
**
** Author(s):
**  - Herve Cuche <hcuche@aldebaran-robotics.com>
**
** Copyright (C) 2012 Herve Cuche
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <event2/util.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <boost/thread.hpp>

#include "transport-client.hpp"

class RemoteService : public TransportClientDelegate {
public:
  RemoteService() {
    tc = new TransportClient("127.0.0.1", 12345);
    tc->setDelegate(this);

    boost::thread transportThread(TransportClient::launch, tc);
    sleep(5);

    tc->send("totot\n");
    transportThread.join();
    delete tc;
  }

  virtual void onConnected()
  {
    std::cout << "connected" << std::endl;
  }

  virtual void onWrite()
  {
    std::cout << "written" << std::endl;
  }

  virtual void onRead()
  {
    std::cout << "read" << std::endl;
  }

private:
  TransportClient *tc;
};

int main(int argc, char *argv[])
{
  RemoteService rs;
  return 0;

}
