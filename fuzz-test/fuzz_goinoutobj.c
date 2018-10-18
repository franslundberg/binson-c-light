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

#define VERIFY(x) if(!(x)) return false

bool fuzz_one_input(const uint8_t *buffer, size_t size)
{

    binson_parser p;

    VERIFY(binson_parser_init(&p, buffer, size));
    VERIFY(binson_parser_go_into_object(&p));
    assert(binson_parser_get_depth(&p) == 1);
    VERIFY(binson_parser_leave_object(&p));
    assert(binson_parser_get_depth(&p) == 0);
    VERIFY(binson_parser_verify(&p));

    printf("}");

    return true;
}

/*======= Local function implementations ====================================*/
