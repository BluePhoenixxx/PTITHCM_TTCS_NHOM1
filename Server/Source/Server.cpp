#include "Server.hpp"
#include <boost/bind.hpp>

extern std::mutex mutex;

Server::Server(boost::asio::io_context &ioContext, int port,
               std::list<std::shared_ptr<IClient>> &clients,
               std::mutex &clientMutex)
    : _clientMutex(clientMutex),
      _acceptor(ioContext, tcp::endpoint(tcp::v4(), port)), _end(false),
      _clientCheck([this]() {
        std::unique_lock<std::mutex> lck(_clientMutex);
        while (!_end) {
          _threadDeath.wait(lck);
          auto it = _clients.begin();
          while (it != _clients.end()) {
            if (*it && std::dynamic_pointer_cast<Session>(*it)->isDead())
              it = _clients.erase(it);
            else
              ++it;
          }
        }
      }),
      _clients(clients),
      _context(boost::asio::ssl::context::sslv23_server) {
        _context.set_options(boost::asio::ssl::context::default_workarounds |
                            boost::asio::ssl::context::no_sslv2 |
                            boost::asio::ssl::context::single_dh_use);
        _context.use_certificate_chain_file("ssl_files/server.crt");
        _context.use_private_key_file("ssl_files/server.key",
                                        boost::asio::ssl::context::pem);
        _context.use_tmp_dh_file("ssl_files/dh512.pem");

        startAccept();
}

// Server::Server(boost::asio::io_service &ioService, int port,
//                std::list<std::shared_ptr<IClient>> &clients,
//                std::mutex &clientMutex)
//     : _clientMutex(clientMutex),
//       _acceptor(ioService, tcp::endpoint(tcp::v4(), port)), _end(false),
//       _clientCheck([this]() {
//         std::unique_lock<std::mutex> lck(_clientMutex);
//         while (!_end) {
//           _threadDeath.wait(lck);
//           auto it = _clients.begin();
//           while (it != _clients.end()) {
//             if (*it && std::dynamic_pointer_cast<Session>(*it)->isDead())
//               it = _clients.erase(it);
//             else
//               ++it;
//           }
//         }
//       }),
//       _clients(clients),
//       _context(boost::asio::ssl::context::sslv23_server) {
  
// }

Server::~Server(void) {
  _end.store(true);
  _threadDeath.notify_all();
  _clientCheck.join();
}

void Server::startAccept(void) {
  Session::sessionPointer awaitingConnection =
      Session::create(_acceptor.get_executor().context(), _context, _threadDeath);
  _acceptor.async_accept(awaitingConnection->getSocket(),
                         boost::bind(&Server::handleAccept, this,
                                     awaitingConnection,
                                     boost::asio::placeholders::error));
}

void Server::handleAccept(Session::sessionPointer &newClient,
                          const boost::system::error_code &error) {
  if (!error) {
    newClient->start();
    _clients.push_back(newClient);
  }
  startAccept();
}
