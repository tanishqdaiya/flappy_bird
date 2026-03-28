#include <stdint.h>

#define FNV_PRIME_32 0x01000193U
#define FNV_OFFSET_BASIS_32 0x811C9DC5U

uint32_t U_Hash(const void* data, size_t size)
{
    uint32_t hash;
    unsigned char *byte;
    
    hash = FNV_OFFSET_BASIS_32;
    byte = (unsigned char*)data;
    for (size_t i = 0; i < size; ++i) {
        hash ^= byte[i];
        hash *= FNV_PRIME_32;
    }
    return hash;
}
