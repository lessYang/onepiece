#ifndef ONEPIECE_BASE_COMMON_H_
#define ONEPIECE_BASE_COMMON_H_

#include <sstream>

#define UNUSED(x) ((void)x)

// yhw
#if 0
#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif
// void dcc_mon_siginfo_handler(int UNUSED(whatsig))
#endif

/**! < 注意INT8的转换这里会变成ascii值, 
 * 如果需要的不是这个结果, 可以用INT代替INT8 */
template <typename out, class in>
out convert(const in & value) {
    std::stringstream stream;
    stream << value;
    out r;
    stream >> r;
    return r;
}

#endif  // ONEPIECE_BASE_COMMON_H_
