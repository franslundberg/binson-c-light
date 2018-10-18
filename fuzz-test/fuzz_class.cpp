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

#include "binson.hpp"

/*======= Local Macro Definitions ===========================================*/
/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/
/*======= Global function implementations ===================================*/

extern "C" bool fuzz_one_input(const uint8_t *data, size_t size)
{
    Binson b;
    binson_parser parser;
    bool ret;
    try {
        b.deserialize(data, size);
        assert(binson_parser_init(&parser, data, size));

        /*
         * if b.deserialize() didn't throw exception
         * this should be a valid binson object.
         * Is not, trigger crash.
         */
        assert(binson_parser_verify(&parser));
        ret = true;
    } catch (const std::runtime_error &e) {
        /* Not a valid binson object */
        ret = false;
    }
    return ret;
}

/*======= Local function implementations ====================================*/
