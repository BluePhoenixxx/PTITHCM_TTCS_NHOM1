#include "BoostNetwork.h"
#include "Client.hpp"
#include "stdafx.h"
#include <iostream>
int main(int argc, char **argv)
{
    try
    {
        ShowWindow(GetConsoleWindow(), 0);
        // ẩn cửa sổ đi
        boost::asio::io_service io_service;
        boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);

        context.load_verify_file("server.crt");
        // khởi tạo client
        Client c("4242", "192.168.128.152", io_service, context);
        // kết nối với server
        c.connectClient();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}