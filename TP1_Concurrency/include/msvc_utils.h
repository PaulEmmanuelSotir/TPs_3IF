#ifndef MSVC_UTILS
#define MSVC_UTILS
#ifdef _MSC_VER

#define SIGUSR2 0
#define SIGUSR1 0

using pid_t = int;

inline void sleep(unsigned int) { };
inline pid_t fork() { return 0; };
inline void waitpid(pid_t, int*, int) { };
inline void kill(pid_t, int);

#endif // _MSC_VER
#endif // MSVC_UTILS

