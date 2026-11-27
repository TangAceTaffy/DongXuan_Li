#ifndef REGISTER_H
#define REGISTER_H
#include "zf_common_headfile.h"
#include <stdint.h>
#include <stddef.h>  // 包含 size_t 的定义

#define PAGE_SIZE 0x10000

#define REG_READ(addr) (*(volatile uint32_t*)(addr))
#define REG_WRITE(addr, val) (*(volatile uint32_t*)(addr) = (val))

void* map_register(uint32_t physical_address, size_t size);

#endif // REGISTER_H