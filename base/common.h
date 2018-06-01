#ifndef ONEPIECE_BASE_COMMON_H_
#define ONEPIECE_BASE_COMMON_H_

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


#endif  // ONEPIECE_BASE_COMMON_H_
