#ifndef __CR_BITSPERLONG_H__
#define __CR_BITSPERLONG_H__

#ifdef CONFIG_32BIT
#define BITS_PER_LONG 32
#else
#define BITS_PER_LONG 64
#endif  /* CONFIG_32BIT */

#endif /* __CR_BITSPERLONG_H__ */
