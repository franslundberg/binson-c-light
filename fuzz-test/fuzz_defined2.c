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
#include <assert.h>

#include "binson_parser.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

static bool parse_binson(uint8_t *buffer, uint32_t size);

/*======= Global function implementations ===================================*/

static int __main(int argc, char **argv)
{

    (void) argc;
    (void) argv;
    ssize_t size;
    uint8_t *buffer_cpy;
    uint8_t buffer[4096];


    size = read(0, buffer, sizeof(buffer));
    bool ret;

    if (size == 0) {
        return -1;
    }

    buffer_cpy = malloc(size);

    if (buffer_cpy == NULL) {
        return -1;
    }

    memcpy(buffer_cpy, buffer, size);
    ret = parse_binson(buffer_cpy, size);

    if (ret) {
        for (ssize_t i = 0; i < size; i++) {
            printf("%02x", buffer_cpy[i]);
        } printf("\r\n");
    }

    free(buffer_cpy);

    return (ret) ? 0 : -1;

}

int main(int argc, char **argv)
{
    #ifdef __AFL_LOOP
    while (__AFL_LOOP(1000)) {
        __main(argc, argv);
    }
    return 0;
    #else
    return __main(argc, argv);
    #endif

}


/*======= Local function implementations ====================================*/

#define VERIFY(x) if(!(x)) return false

static bool parse_binson(uint8_t *buffer, uint32_t size)
{

    binson_parser p;

    binson_parser_init(&p, buffer, size);
    VERIFY(binson_parser_verify(&p));
    VERIFY(binson_parser_go_into_object(&p));
    VERIFY(binson_parser_get_depth(&p) == 1);

    VERIFY(binson_parser_next(&p));
    bbuf *data;
    data = binson_parser_get_name(&p);
    VERIFY(data->bsize == 1);
    VERIFY(data->bptr[0] == 0x41);
    VERIFY(binson_parser_get_type(&p) == BINSON_TYPE_STRING);
    data = binson_parser_get_string_bbuf(&p);
    VERIFY(data->bsize == 1);
    VERIFY(data->bptr[0] == 0x41);
    VERIFY(!binson_parser_next(&p));
    VERIFY(binson_parser_leave_object(&p));
    assert(p.buffer_used == size);
    uint8_t expected[8] = { /* 4014014114014141*/
        0x40, 0x14, 0x01, 0x41, 0x14, 0x01, 0x41, 0x41
    };
    assert(memcmp(buffer, expected, size) == 0);


    return true;
}
