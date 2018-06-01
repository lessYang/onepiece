#include "net/tcp.h"

#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <netinet/in.h>     // IPV6_
#include <netinet/tcp.h>    // TCP_NODELAY
#include <sys/types.h>
#include <sys/socket.h>

#include "base/common.h"

namespace base {

static int _netSetV6Only(SOCKET s, bool isv6);
static int _netSetBlock(SOCKET s, int non_block); 

bool TCP::isValidPort(int port) noexcept {    
    return port >= 0 && port <= MAX_SOCKET_PORT;
}

void TCP::close(SOCKET sfd) noexcept {
    if (sfd != INVALID_SOCKET) {
        ::shutdown(sfd, SHUT_RDWR);
    }
    ::close(sfd);
}

int TCP::reuseAddr(SOCKET sfd) noexcept {
    int yes = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR,
                   reinterpret_cast<void*>(&yes), sizeof(yes)) == -1) {
        return -1;
    }
    return 0;
}

int TCP::reusePort(SOCKET sfd) noexcept {
    int yes = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT,
                   reinterpret_cast<void*>(&yes), sizeof(yes)) == -1) {
        return -1;
    }
    return 0;
}

int TCP::v6Only(int sfd) noexcept {
    return _netSetV6Only(sfd, true);
}

int TCP::notV6Only(int sfd) noexcept {
    return _netSetV6Only(sfd, false);
}

int TCP::nonBlock(int sfd) noexcept {
    return _netSetBlock(sfd, 1);
}

int TCP::block(int sfd) noexcept {
    return _netSetBlock(sfd, 0);
}

int TCP::keepAlive(int sfd) noexcept {
    int yes = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE,
        reinterpret_cast<void*>(&yes), sizeof(yes)) == -1) {
        return -1;
    }
    return 0;
}

int TCP::setLinger(SOCKET sfd, struct linger *ling) noexcept {
    if (setsockopt(sfd, SOL_SOCKET, SO_LINGER,
        reinterpret_cast<void*>(ling), sizeof(struct linger)) == -1) {
        return -1;
    }
    return 0;
}

int TCP::setTimeout(SOCKET sfd, int ms, int optname) {
    if (ms < 0 || INVALID_SOCKET == sfd) {
        return -1;
    }
    struct timeval t = {(int)(ms / 1000), (int)((ms % 1000) * 1000)};
    return setsockopt(sfd, SOL_SOCKET, optname, reinterpret_cast<void*>(&t), sizeof(t));
}

int TCP::noDelay(SOCKET sfd) noexcept {
    int one = 1;
    // Set TCP nodelay if available, MAC OS X Hack
    // See http://lists.danga.com/pipermail/memcached/2005-March/001240.html
    #ifndef TCP_NOPUSH
      if (setsockopt(sfd, IPPROTO_TCP, TCP_NODELAY,
          reinterpret_cast<void*>(&one), sizeof(one)) == -1) {
          return -1;
      }
    #endif
    return 0;
}

int TCP::read(SOCKET sfd, uint8_t *buf, size_t len) {
    if (buf == nullptr || len == 0 || sfd == INVALID_SOCKET) {
        return -1;
    }

    int8_t retries = 0;
    int got = 0;

    while(true) {
        got = static_cast<int>(recv(sfd, (void*)buf, len, 0));
        if (got < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
                if (retries++ < 5) {
                    continue;
                }
            }
            if (errno == ECONNRESET) {
                break;
            } else if (errno == ENOTCONN) {
                break;
            } else if (errno == ETIMEDOUT) {
                break;
            } else {
                break;
            }
        }
        break;
    }
#if 0
    if (got < 0) {
        LOG("recv error %d, %s, file->%s:%d\n", errno, strerror(errno),
            __FUNCTION__, __LINE__);
    }
#endif
    return got;
}

int TCP::write(SOCKET sfd, const uint8_t *buf, size_t len) {
    if (buf == nullptr || len == 0 || sfd == INVALID_SOCKET) {
        return -1;
    }
    int32_t sent = 0;
    int flags = 0;
#ifdef MSG_NOSIGNAL
    flags |= MSG_NOSIGNAL;
#endif
    int b = static_cast<int>(send(sfd, (void*)(buf+sent), len - sent, flags));
    if (b < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            return 0;
        }
        if (errno == EPIPE || errno == ECONNRESET || errno == ENOTCONN) {
            return -1;
        }
        return -1;
    }
    if (b == 0) {
        return -1;
    }
    return b;
}

#if 0
int TCP::accept(SOCKET sfd, void (*f)(int, int, uint64_t, void *), void *data) {

    socklen_t addrLen;
    sockaddr_storage addrStorage;
    sockaddr* addrp = (sockaddr*)&addrStorage;
    addrLen = sizeof(addrStorage);

    int clientSocket = INVALID_SOCKET;

    uint64_t ip = 0;
    int port = 0;
    if (f == NULL) {
        f = _defaultAccept;
    }
    // Accept as many new clients as possible, even though libevent signaled only
    // one, this helps us to avoid having to go back into the libevent engine so
    // many times
    while ((clientSocket = ::accept(sfd, addrp, &addrLen)) != -1) {
        // If we're overloaded, take action here
        ip = 0;
        port = 0;
        if (addrp->sa_family == AF_INET) {
            sockaddr_in * ipv4 = (sockaddr_in*)addrp;
            ip = ipv4->sin_addr.s_addr;
            port = ipv4->sin_port;
        } else if (addrp->sa_family == AF_INET6){
            sockaddr_in6 * ipv6 = (sockaddr_in6*)addrp;
            ip = ipv6->sin6_addr.__in6_u.__u6_addr32[3];
            port = ipv6->sin6_port;
        }
        f(clientSocket, port, ip, data);
        // Explicitly set this socket to NONBLOCK mode
        // netNonBlock(clientSocket);
        addrLen = sizeof(addrStorage);
    }
    // Done looping accept, now we have to make sure the error is due to
    // blocking. Any other error is a problem
    if (errno != EAGAIN && errno != EWOULDBLOCK) {
        return -1;
    }

    return 0;
}
#endif

////////////////////////

#if 0
static void _defaultAccept(int socket, int port, uint64_t ip, void *data) {
    UNUSED(data);
    UNUSED(port);
    UNUSED(ip);
    TCP::close(socket);
}
#endif

static int _netSetV6Only(int s, bool isv6) {
    int flag = isv6 ? 1 : 0;
    if (setsockopt(s,IPPROTO_IPV6,IPV6_V6ONLY,
                   reinterpret_cast<void*>(&flag),sizeof(flag)) == -1) {
        return -1;
    }
    return 0;
}

static int _netSetBlock(SOCKET s, int non_block) {
    int flags;
    /* Set the socket blocking (if non_block is zero) or non-blocking.
     * Note that fcntl(2) for F_GETFL and F_SETFL can't be
     * interrupted by a signal. */
    if ((flags = fcntl(s, F_GETFL)) == -1) {
        return -1;
    }

    if (non_block)
        flags |= O_NONBLOCK;
    else
        flags &= ~O_NONBLOCK;

    if (fcntl(s, F_SETFL, flags) == -1) {
        return -1;
    }
    return 0;
}

}  // end namespace base
