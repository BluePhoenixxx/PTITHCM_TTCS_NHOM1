#include "CommandHandler.hpp"
#include "algorithm"
#include "sstream"

using namespace std;

/* CommandHandler
+ Constructor nhận danh sách tham chiếu đến danh sách các client, 
 một mutex và một biến flag(coreQuit) để theo dõi việc thoát server core. 
 Constructor này khởi tạo một _commands ánh xạ các chuỗi lệnh vào các 
 phương thức của lớp.
 */
CommandHandler::CommandHandler(list<shared_ptr<IClient>> &clients, 
                                mutex &clientMutex, bool coreQuit) :
    _commands({
            {"help", &CommandHandler::help},
            {"send", &CommandHandler::send},
            {"list", &CommandHandler::listCmd},
            {"requestCodes", &CommandHandler::requestCodes},
            {"quit", &CommandHandler::quit}
        }),

    _clients(clients),
    _clientMutex(clientMutex),
    _coreQuit(coreQuit){

}

/* executeCommand
 + Hàm này nhận một command line và thực thi nó bằng cách phân tích cú pháp 
 và gọi phương thức tương ứng.
*/
void CommandHandler::executeCommand(string const &line){
    vector<string> command = parseCommand(line);
    if (command.empty() || _commands.find(command[0]) == _commands.end()){
        cerr << "unknown command type help for help" << endl;
        prompt();
        return;
    }
    (this->*_commands[command[0]])(command);
    prompt();
}

/*
+ Hàm này phân tích một command thành các token riêng lẻ dựa trên khoảng 
trắng.
*/
vector<string> CommandHandler::parseCommand(string const &command){
    stringstream ss(command);
    vector<string> commands;
    string input;

    while(getline(ss, input, ' '))
        commands.push_back(input);
    return (commands);
}

/* help
+ In ra danh sách các lệnh có sẵn cùng với hướng dẫn sử dụng.
*/
void CommandHandler::help(vector<string> const & /* command */){
    cout << "Command : " << endl
         << "\thelp - list available commands" << endl
         << "\tquit - quit" << endl
         << "\tlist - list clients" << endl
         << "\tsend [clientNb] [requestCode] - send"
         << "to client [clientNb] the [requestCode]" << endl
         << "\trequestCodes - list request codes" << endl;
}

/* listCmd
+ In ra danh sách các client đang kết nối.
*/
void CommandHandler::listCmd(vector<string> const & /* command */){
    _clientMutex.lock();
    auto &last = *(--_clients.end());
    for (auto &it : _clients){
        cout << "Client [" << it->getId() << "]";
        if (&it != &last)
            cout << " - ";
    }
    (!_clients.empty()) ? cout << endl
                        : cout << "no client connected" << endl;
    _clientMutex.unlock();
}

/* send
+ Gửi một yêu cầu đến một client cụ thể.
*/
void CommandHandler::send(vector<string> const &command){
    if (command.size() != 3 ||
        !all_of(command[1].begin(), command[1].end(), ::isdigit) ||
        !all_of(command[2].begin(), command[2].end(), ::isdigit)){
            cerr << "invalid arguments" << endl;
            return;
        }
    
    unsigned id = stoi(command[1]);
    bool found = false;
    _clientMutex.lock();
    for (auto &it : _clients)
        if (it->getId() == id){
            if (it->writeReady())
                it->sendState(stoi(command[2]));
            else{
                cerr << "client not ready" << endl;
                _clientMutex.unlock();
                return;
            }
        }
        found = true;
    _clientMutex.unlock();
    (found) ? cout << "request sent" << endl
            : cerr << "client not found" << endl;
}

/* requestCodes
+  In ra danh sách mã yêu cầu có sẵn.
*/
void CommandHandler::requestCodes(vector<string> const & /* command */){
    cout << "Request codes :" << endl
         << "0 - ping" << endl
         << "1 - ask id" << endl
         << "2 - activate keyboard tracking (3 - deactivate)" << endl
         << "4 - activate mouse movement tracking (5 - deactivate)" << endl
         << "6 - activate mouse clicking tracking (7 - deactivate)" << endl
         << "8 - disconnect client" << endl
         << "9 - pause client (10 - unpause)" << endl
         << "11 - set frequency (not implenmented)" << endl
         << "12 - get status" << endl;
}

/* quit
+  Đặt biến _coreQuit thành true, cho biết rằng máy chủ nên thoát.
*/
void CommandHandler::quit(vector<string> const & /* command */){
    _coreQuit = true;
}

/* prompt
+  In ra dấu nhắc lệnh để người dùng nhập lệnh tiếp theo.
*/
void CommandHandler::prompt() {cout << "server >> " << flush; }