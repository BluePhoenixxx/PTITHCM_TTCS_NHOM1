
//Hàm main của Key logger

#include <iostream>
//#include "Core.hpp"
using namespace std;

int main(int ac, char **av){
    if(ac != 2){
        cerr<<"Usage : ./server [port]"<<endl;
        return (EXIT_FAILURE);        
    }
    
    try
    {
        /* code */
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
    return (EXIT_SUCCESS);
}


