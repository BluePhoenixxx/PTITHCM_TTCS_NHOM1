#ifndef DATAFACTORY_HPP
#define DATAFACTORY_HPP

#include <map>
#include <memory>
#include <vector>

using namespace std;

/* DataObject đại diện cho kiểu của đối tượng đc tạo bởi factory,
 và key với mỗi key để phân biệt các đối tượng */
template <class DataObject, class Key = int> class DataFactory{

private:
    /* Sử dụng để lưu trữ các creator cho mỗi kiểu dữ 
    liệu của đối tượng mà factory có thể tạo ra*/
    map<Key, shared_ptr<DataObject>> _instanceCreator; 

public:
    DataFactory() = default; //Hàm khởi tạo
    ~DataFactory() = default; //Hàm hủy

    /* Gán key ứng với 1 share_ptr có kiểu DataObject, nếu key đã tồn tại thì hàm
    này ko làm gì hết*/
    void feedCreator(Key key, shared_ptr<DataObject> dataObj){
        if (_instanceCreator.find(key) == _instanceCreator.end())
            _instanceCreator[key] = dataObj;
    }
    
    /* Tạo instance của 1 DataObject ứng với 1 khóa tương ứng và khởi tạo với giá trị
    đc truyền vào, Bằng cách tìm khóa trong _instanceCreator map, lấy share_ptr ứng 
    với creator và khởi chạy hàm make_shared để tạo instance*/
    shared_ptr<DataObject> createInstance(const Key &key, const vector<char> &data){
        shared_ptr<DataObject> tmpObj = nullptr;
        auto it = _instanceCreator.find(key);

        if(it != _instanceCreator.end())
            tmpObj = make_shared<DataObject>(data);
        return tmpObj;
    }

private:
    /* Xóa bản sao của constructor để tránh việc sao chép của đối tượng DataObject */
    DataFactory(const DataFactory &cp) = delete;
    /* Xóa bản sao của toán tử gán để tránh gán đối tượng DataFactory */
    DataFactory &operator=(const DataFactory &cp) = delete;

};

#endif /* DATAFACTORY_HPP */