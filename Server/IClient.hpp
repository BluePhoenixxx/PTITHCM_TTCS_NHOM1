#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#include <vector>

using namespace std;

class IClient {
public:
  virtual ~IClient(void) {}

  virtual void sendState(int state) = 0;
  virtual vector<char> receiveData(void) = 0;
  virtual unsigned getId(void) const = 0;
  virtual bool dataAvailable(void) = 0;
  virtual bool writeReady(void) const = 0;
};

#endif // ICLIENT_HPP_