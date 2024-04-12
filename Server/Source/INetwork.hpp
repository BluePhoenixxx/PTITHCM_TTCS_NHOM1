#ifndef INETWORK_HPP_
#define INETWORK_HPP_

#include "IClient.hpp"
#include <list>
#include <memory>
#include <mutex>
#include <string>

using namespace std;

class INetwork{
public:
    virtual ~INetwork() = default;

    virtual void startServer(unsigned short port, 
                            list<shared_ptr<IClient>> &clients, 
                            mutex &clientMutex) = 0;
};

#endif /* INETWORK_HPP_ */