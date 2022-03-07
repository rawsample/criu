#ifndef COMPEL_HANDLE_ELF_H__
#define COMPEL_HANDLE_ELF_H__


#ifdef CONFIG_32BIT
#include "elf32-types.h"
#define __handle_elf			     handle_elf_mips32

#else
#include "elf64-types.h"
#define __handle_elf			     handle_elf_mips64
#endif  /* CONFIG_32BIT */

#define arch_is_machine_supported(e_machine) (e_machine == EM_MIPS)

extern int handle_elf_mips32(void *mem, size_t size);
extern int handle_elf_mips64(void *mem, size_t size);

#endif /* COMPEL_HANDLE_ELF_H__ */
