#ifndef MYKERNEL_KGETS_H
#define MYKERNEL_KGETS_H

#include <misc/types.h>
#include <misc/gcc.h>

/*
 * writes into buffer buf (for dest buf max size) not including \n
 * returns -1 if failure (if dest buf max size exceeded) >= 0 
 * which is # of total bytes written into buf
 */
__mykapi mykt_int_32 kgets(mykt_int_8*, mykt_uint_32);

#endif
