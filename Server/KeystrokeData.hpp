#ifndef KEYSTROKEDATA_HPP_
#define KEYSTROKEDATA_HPP_

#include "IData.hpp"

using namespace std;

class KeystrokeData: public IData{
public:
    KeystrokeData();
    KeystrokeData(const vector<char> &data);

    virtual ~KeystrokeData() = default;

protected:
    int _timestamp;
    int _key;
    int _procName[256];

public:
    virtual void dump() const;
    virtual string getData() const;
    virtual shared_ptr<IData> cloneObj(const vector<char> &data);
    virtual void feedObj(const vector<char> &data);

private:
    KeystrokeData(const KeystrokeData &cp) = delete;
    KeystrokeData &operator=(const KeystrokeData &cp) = delete;

};

#endif /* KEYSTROKEDATA_HPP_ */