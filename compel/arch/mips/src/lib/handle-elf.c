#include <string.h>
#include <errno.h>

#include "handle-elf.h"
#include "piegen.h"
#include "log.h"

#ifdef CONFIG_32BIT
static const unsigned char __maybe_unused elf_ident_32_be[EI_NIDENT] = {
	0x7f, 0x45, 0x4c, 0x46, 0x01, 0x02, 0x01, 0x00, /* clang-format */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#else
static const unsigned char __maybe_unused elf_ident_64_le[EI_NIDENT] = {
	0x7f, 0x45, 0x4c, 0x46, 0x02, 0x01, 0x01, 0x00, /* clang-format */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#endif  /* CONFIG_32BIT */


int handle_binary(void *mem, size_t size)
{
#ifdef CONFIG_32BIT
	if (memcmp(mem, elf_ident_32_be, sizeof(elf_ident_32_be)) == 0)
		return handle_elf_mips32(mem, size);

#else
	if (memcmp(mem, elf_ident_64_le, sizeof(elf_ident_64_le)) == 0)
		return handle_elf_mips64(mem, size);
#endif  /* CONFIG_32BIT */

	pr_err("Unsupported Elf format detected\n");
	return -EINVAL;
}
