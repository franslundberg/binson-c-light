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

    bbuf *buf = NULL;

    VERIFY(binson_parser_init(&p, buffer, size));
    VERIFY(binson_parser_go_into_object(&p));
    VERIFY(binson_parser_get_depth(&p) == 1);

    printf("{\r\n");

    VERIFY(binson_parser_field_ensure(&p, "A", BINSON_ID_STRING));
    buf = binson_parser_get_string_bbuf(&p);
    VERIFY( buf->bptr != NULL);
    printf("    \"A\": %*.*s,\r\n", 0, (int) buf->bsize, (const char *) buf->bptr);


    VERIFY(binson_parser_field_ensure(&p, "B", BINSON_ID_INTEGER));
    printf("    \"B\": %d,\r\n", (int) binson_parser_get_integer(&p));

    VERIFY(binson_parser_field_ensure(&p, "C", BINSON_ID_DOUBLE));
    printf("    \"C\": %f,\r\n", (float) binson_parser_get_double(&p));

    VERIFY(binson_parser_field_ensure(&p, "D", BINSON_ID_BOOLEAN));
    printf("    \"D\": %s,\r\n", binson_parser_get_boolean(&p) ? "true" : "false");

    VERIFY(binson_parser_field_ensure(&p, "E", BINSON_ID_BYTES));
    buf = binson_parser_get_bytes_bbuf(&p);
    VERIFY(buf->bptr != NULL);
    printf("    \"E\": ");
    if (buf->bsize > 0) {
        printf("0x");
        for (size_t i = 0; i < buf->bsize; i++) {
            printf("%02x", buf->bptr[i]);
        }
    }
    printf(",\r\n");

    VERIFY(binson_parser_field_ensure(&p, "F", BINSON_ID_OBJECT));
    VERIFY(binson_parser_go_into_object(&p));
    VERIFY(binson_parser_get_depth(&p) == 2);
    VERIFY(binson_parser_leave_object(&p));
    VERIFY(binson_parser_get_depth(&p) == 1);

    printf("    \"F\":{},\r\n");

    VERIFY(binson_parser_field_ensure(&p, "G", BINSON_ID_ARRAY));
    VERIFY(binson_parser_go_into_array(&p));
    VERIFY(binson_parser_leave_array(&p));

    printf("    \"G\":[],\r\n");

    VERIFY(binson_parser_leave_object(&p));
    assert(binson_parser_get_depth(&p) == 0);
    VERIFY(binson_parser_verify(&p));

    printf("}");

    return true;
}


/*======= Local function implementations ====================================*/
