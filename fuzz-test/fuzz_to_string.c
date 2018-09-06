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
/*======= Global function implementations ===================================*/

static int __main(int argc, char **argv)
{

    (void) argc;
    (void) argv;

    ssize_t size;
    uint8_t *buffer_cpy;
    uint8_t buffer[4096];
    char *str_buffer;


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
    binson_parser p;
    size_t psize = 0;
    binson_parser_init(&p, buffer, size);
    ret = binson_parser_to_string(&p, NULL, &psize, true);
    if (ret) {
        str_buffer = malloc(psize);
        if (str_buffer == NULL) {
            free(buffer_cpy);
            return -1;
        }
        ret = binson_parser_to_string(&p, str_buffer, &psize, true);
        assert(ret);
        printf("%*.*s\r\n", 0, (int) psize, str_buffer);
        for (ssize_t i = 0; i < size; i++) {
            printf("%02x", buffer_cpy[i]);
        } printf("\r\n");
        free(str_buffer);

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
