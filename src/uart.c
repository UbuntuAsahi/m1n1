/* SPDX-License-Identifier: MIT */

#include <stdarg.h>

#include "types.h"
#include "uart.h"
#include "utils.h"
#include "vsprintf.h"

#define UART_BASE 0x235200000L

#define ULCON 0x000
#define UCON 0x004
#define UFCON 0x008
#define UTRSTAT 0x010
#define UTXH 0x020
#define URXH 0x024
#define UBRDIV 0x028
#define UFRACVAL 0x02c

void *pxx = uart_init;

void uart_init(void)
{
    /* keep UART config from iBoot */
}

void uart_putbyte(u8 c)
{
    while (!(read32(UART_BASE + UTRSTAT) & 0x02))
        ;

    write32(UART_BASE + UTXH, c);
}

u8 uart_getbyte(void)
{
    while (!(read32(UART_BASE + UTRSTAT) & 0x01))
        ;

    return read32(UART_BASE + URXH);
}

void uart_putchar(u8 c)
{
    if (c == '\n')
        uart_putbyte('\r');

    uart_putbyte(c);
}

u8 uart_getchar(void)
{
    return 0;
}

void uart_puts(const char *s)
{
    while (*s)
        uart_putchar(*(s++));

    uart_putchar('\n');
}

void uart_write(const void *buf, size_t count)
{
    const u8 *p = buf;

    while (count--)
        uart_putbyte(*p++);
}

size_t uart_read(const void *buf, size_t count)
{
    return 0;
}
