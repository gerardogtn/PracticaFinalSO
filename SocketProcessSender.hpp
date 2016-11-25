// Copyright 2016
#ifndef SOCKETPROCESSSENDER_H
#define SOCKETPROCESSSENDER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <exception>
#include <string>
#include "SchedulerResult.hpp"

class SocketProcessSender {
 private:
  struct sockaddr_in serverAddress;
  struct hostent *server;
  int port;
  int socketd;

  void createSocket() {
    socketd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketd < 0) {
      throw std::runtime_error("Error opening socket");
    }
  }

  void startServer() {
    server = gethostbyname("127.0.0.1");
    if (server == 0) {
     throw std::runtime_error("Error no host available");
    }
  }

  void setServerAddress() {
    bzero(reinterpret_cast<char *>(&serverAddress), sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    bcopy(reinterpret_cast<char *> (server->h_addr),
          reinterpret_cast<char *> (&serverAddress.sin_addr.s_addr),
         server->h_length);
    serverAddress.sin_port = htons(port);
  }

  void connectToSocket() {
    auto connectionResult = connect(socketd,
      (struct sockaddr *) &serverAddress,
      sizeof(serverAddress));
    if (connectionResult < 0)
        throw std::runtime_error("Cannot connect to socket");
  }

  void writeSafely(const char* message) {
    int n = ::send(socketd, message, 1024, 0);
    if (n < 0) {
      end();
      throw std::runtime_error("Error writing to socket.");
    }
  }

  void writeSafely(std::string string) {
    writeSafely(string.c_str());
  }

  void start() {
    createSocket();
    startServer();
    setServerAddress();
    connectToSocket();
  }

  void end() {
    close(socketd);
  }

 public:
  explicit SocketProcessSender(int port) : port(port) {}

  virtual ~SocketProcessSender() {}

  void send(std::string title, const SchedulerResult& result) {
    start();
    writeSafely(title +
      "\n" +
      "Average wait time: " +
      std::to_string(result.getAverageWaitTime()) +
      "\n" +
      "Average turn around time: " +
      std::to_string(result.getAverageTurnAroundTime()) +
      "\n\n");
    end();
  }
};

#endif  // SOCKETPROCESSSENDER_H
