#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#include <vector>

using namespace std;

class IClient{
public:
    virtual ~IClient() {}

    virtual void sendState(int state) = 0;
    virtual vector<char> receiveData() = 0;
    virtual unsigned getId() const = 0;
    virtual bool dataAvailable() = 0;
    virtual bool writeReady() const = 0;

};

#endif /* ICLIENT_HPP_ */ 