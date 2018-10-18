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

bool fuzz_one_input(const uint8_t *data, size_t size)
{
    bool ret;
    binson_parser parser;
    ret = binson_parser_init_array(&parser, data, size);
    if (ret) {
        ret = binson_parser_verify(&parser);
        if (ret) {
            assert(binson_parser_go_into_array(&parser));
            assert(binson_parser_leave_array(&parser));
        }
    }
    return ret;
}

/*======= Local function implementations ====================================*/
