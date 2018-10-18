/**
 * @file binson_fuzz.c.c
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>

#include "binson_parser.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/
/*======= Global function implementations ===================================*/

bool fuzz_one_input(const uint8_t *data, size_t size)
{
    bool ret;
    char str_buffer[8192];
    binson_parser p;
    size_t psize = sizeof(str_buffer);
    binson_parser_init(&p, data, size);
    ret = binson_parser_to_string(&p, str_buffer, &psize, true);
    printf("%*.*s\r\n", 0, (int) psize, (char*) str_buffer);
    ret |= binson_parser_to_string(&p, str_buffer, &psize, false);
    printf("%*.*s\r\n", 0, (int) psize, (char*) str_buffer);
    return ret;
}

/*======= Local function implementations ====================================*/
