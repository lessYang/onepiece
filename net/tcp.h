#ifndef ONEPIECE_NET_TCP_H_
#define ONEPIECE_NET_TCP_H_

#include <string>
#include <memory>

#include <arpa/inet.h>

#include "net/net.h"

namespace base {

class TCP {
public:
    TCP() = default;
    ~TCP() = default;

    static bool isValidPort(int port) noexcept;
    static void close(SOCKET sfd) noexcept;
    static int reuseAddr(SOCKET sfd) noexcept;
    static int reusePort(SOCKET sfd) noexcept;
    static int v6Only(SOCKET sfd) noexcept;
    static int notV6Only(SOCKET sfd) noexcept;
    static int nonBlock(SOCKET sfd) noexcept;
    static int block(SOCKET sfd) noexcept;
    static int keepAlive(SOCKET sfd) noexcept;
    static int noDelay(SOCKET sfd) noexcept;

    static int setLinger(SOCKET sfd, struct linger* ling) noexcept;
    static int setTimeout(SOCKET sfd, int ms, int optname);

    /**
       * @brief read
       * @param sfd
       * @param buf
       * @param len
       * @return 0 peer shutdown, -1 error
       */
    static int read(SOCKET sfd, uint8_t* buf, size_t len);

    /**
        * @brief write
        * @param fd
        * @param buf
        * @param len
        * @return -1 system error,
        *  HOLLY_NERR_PTR buf error, HOLLY_NERR_LEN len error
        */
       static int write(SOCKET sfd, const uint8_t* buf, size_t len);

       /**
        * @brief accept
        * @param sfd
        * @param f (socket, port, ip, data)
        * @param data data set to f
        * @return
        */
       //static int accept(SOCKET sfd, void(*f)(int, int, uint64_t, void*), void *data);
};

}  // end namespace base

#endif  // ONEPIECE_NET_TCP_H_
