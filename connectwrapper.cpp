#include "connectwrapper.h"
#include <unistd.h>






ConnectWrapper::ConnectWrapper()
{
}

int ConnectWrapper::remoteConnect(int msockfd,  struct sockaddr *ai_addr , socklen_t ai_addrlen)
{

    return connect(msockfd,  ai_addr , ai_addrlen);

}


int ConnectWrapper::remoteClose(int msockfd)
{
    return close(msockfd);
}
