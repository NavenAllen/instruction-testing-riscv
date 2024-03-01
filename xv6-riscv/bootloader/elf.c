#include "types.h"
#include "param.h"
#include "layout.h"
#include "riscv.h"
#include "defs.h"
#include "buf.h"
#include "elf.h"

#include <stdbool.h>

struct elfhdr* kernel_elfhdr;
struct proghdr* kernel_phdr;

uint64 find_kernel_load_addr(enum kernel ktype) {
    /* CSE 536: Get kernel load address from headers */
    uint64 start_addr;
    if (ktype == NORMAL) {
        start_addr = RAMDISK;
    } else {
        start_addr = RECOVERYDISK;
    }
    kernel_elfhdr = (struct elfhdr *) start_addr;
    uint64 phoff = kernel_elfhdr->phoff;
    ushort phsize = kernel_elfhdr->phentsize;

    kernel_phdr = (struct proghdr *) (start_addr + phoff + phsize);
    uint64 kernel_load_addr = kernel_phdr->vaddr;
    return kernel_load_addr;
}

uint64 find_kernel_size(enum kernel ktype) {
    uint64 start_addr;
    if (ktype == NORMAL) {
        start_addr = RAMDISK;
    } else {
        start_addr = RECOVERYDISK;
    }
    kernel_elfhdr = (struct elfhdr *) start_addr;
    uint64 shoff = kernel_elfhdr->shoff;
    ushort shnum = kernel_elfhdr->shnum;
    ushort shsize = kernel_elfhdr->shentsize;

    uint64 kernel_size = shoff + shnum*shsize;
    return kernel_size;
}

uint64 find_kernel_entry_addr(enum kernel ktype) {
    uint64 start_addr;
    if (ktype == NORMAL) {
        start_addr = RAMDISK;
    } else {
        start_addr = RECOVERYDISK;
    }
    kernel_elfhdr = (struct elfhdr *) start_addr;
    return kernel_elfhdr->entry;
}