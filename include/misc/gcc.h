#ifndef COMMON_GCC_H
#define COMMON_GCC_H

#define __mykapi __attribute__((fastcall))
#define unlikely(expr) __builtin_expect(expr, 0)
#define likely(expr) __builtin_expect(expr, 1)
#define packed __attribute__((packed))
#define dont_optimize __attribute__((optimize("O0")))
#define omit_frame_pointer __attribute__((optimize("omit-frame-pointer")))
#define unused __attribute__((unused))
#define aligned(n) __attribute__((aligned(n)))
#define noinline __attribute__((noinline))

#endif
