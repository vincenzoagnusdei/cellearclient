#ifndef CONNECTWRAPPER_H
#define CONNECTWRAPPER_H

#include <sys/socket.h>



class ConnectWrapper
{
public:
    ConnectWrapper();


    // call connect to associate remote address with socket
    int remoteConnect(int msockfd,  struct sockaddr *ai_addr , socklen_t ai_addrlen);

    int remoteClose(int msockfd);


};

#endif // CONNECTWRAPPER_H
