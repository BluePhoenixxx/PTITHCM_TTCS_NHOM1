#ifndef STATUSDATA_HPP_
#define STATUSDATA_HPP_

#include "IData.hpp"
#include "Protocol.hpp"

class StatusData : public IData{
public:
    StatusData();
    StatusData(const vector<char> &data);

    virtual ~StatusData() = default;

protected:
    PTITKeyLogger::t_status _status; //biến lưu trữ trạng thái

public:
    virtual void dump() const;
    virtual string getData() const;
    virtual shared_ptr<IData> cloneObj(const vector<char> &data);
    virtual void feedObj(const vector<char> &data);

private:
    StatusData(const StatusData &cp) = delete;
    StatusData &operator=(const StatusData &cp) = delete;

    const string boolToString(const bool &val) const; //Chuyển giá trị bool sang chuỗi

};

#endif /* STATUSDATA_HPP_ */