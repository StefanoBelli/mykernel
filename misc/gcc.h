#ifndef COMMON_GCC_H
#define COMMON_GCC_H

#define __mykapi __attribute__((fastcall))
#define unlikely(expr) __builtin_expect(expr, 0)
#define likely(expr) __builtin_expect(expr, 1)
#define packed __attribute__((packed))
#define interrupt __attribute__((interrupt))

#endif
