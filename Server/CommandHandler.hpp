#ifndef COMMANDHANDLER_HPP_
#define COMMANDHANDLER_HPP_

#include "IClient.hpp"
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>

using namespace std;

class CommandHandler{
    typedef void (CommandHandler::*Command)(
        vector<string> const &conmmand);

    //1 map ko có thứ tự ánh xạ các chuỗi lệnh sang các hàm thành viên Command
    unordered_map<string, Command> _commands;

    //1 tham chiếu đến 1 danh sách các shared_ptr tới đối tượng IClient
    list<shared_ptr<IClient>> &_clients;

    //1 tham chiếu đến 1 khóa chặn đc sử dụng để đồng bộ hóa truy cập vào ds Client
    mutex &_clientMutex;

    //1 tham chiếu đến 1 cờ boolean cho biết liệu core server có nên thoát hay ko
    bool &_coreQuit;

public:
    // CommandHandler(list<shared_ptr<IClient>> &clients, mutex &clientMutex, 
    //                                     bool &coreQuit);

    ~CommandHandler() = default;

    void executeCommand(string const &line);

public:
    CommandHandler(list<shared_ptr<IClient>> &clients, mutex &clientMutex, 
                    bool coreQuit);

    vector<string> parseCommand(string const &command);
    void help(vector<string> const & /* command */);
    void send(vector<string> const & command);
    void listClient(vector<string> const & /* command */);
    void requestCodes(vector<string> const & /* command */);
    void quit(vector<string> const & /* command */);
    void prompt();

};

#endif /* COMMANDHANDLER_HPP_ */