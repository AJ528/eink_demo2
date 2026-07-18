
// header guard
#ifndef __MPRINTF_H
#define __MPRINTF_H


#include <stdarg.h>
#include <stdint.h>

int32_t puts_(const char * restrict str);
int32_t println_(const char * restrict str);
int32_t printfln_(const char * restrict format_str, ...);
int32_t printf_(const char * restrict format_str, ...);
int32_t sprintf_(char * restrict out_str, const char * restrict format_str, ...);
int32_t snprintf_(char * restrict out_str, uint32_t buf_len, const char * restrict format_str, ...);
int32_t vsnprintf_(char * restrict out_str, uint32_t buf_len, const char * restrict format_str, va_list arg);
char * strncpy_(char * restrict dest_str, const char * restrict src_str, uint32_t len);
uint32_t strlen_(const char * restrict str);
int32_t print_newline(void);

// Unlike the other string.h functions, memset cannot end in an underscore.
// This is so the gnu linker will find and call the function when needed.
void* memset(void *ptr, uint8_t value, uint32_t num);

int32_t strcmp_(const char *str1, const char *str2);
void* memmove_(void *destination, const void *source, uint32_t num);
void* memcpy_(void *destination, const void *source, uint32_t num);

#endif // __MPRINTF_H