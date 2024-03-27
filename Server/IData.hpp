#ifndef IDATA_HPP_
#define IDATA_HPP_

#include <memory>
#include <vector>

using namespace std;

class IData{
    public:
        virtual ~IData() = default;
        virtual void dump() const = 0;
        virtual string getData() const = 0;
        virtual shared_ptr<IData> cloneObj(const vector<char> &data) = 0;
        virtual void feedObj(const vector<char> &data) = 0;

};

#endif /* IDATA_HPP_ */