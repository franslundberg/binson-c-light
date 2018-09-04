/**
 * @file binson_parser_init.c
 *
 * Description
 *
 */

/*======= Includes ==========================================================*/

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "binson_defines.h"
#include "binson_parser.h"
#include "binson_writer.h"
#include "utest.h"

/*======= Local Macro Definitions ===========================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/

/*
{
  "A": "B", 
  "B": {
    "A": "B"
  }, 
  "C": [
    "A",
    "A",
    {
      "A": "B", 
      "B": [
        "A",
        "A",
        {
          "A": "B"
        },
        [
          [
            [
              [
                {
                  "A": "B"
                }
              ]
            ]
          ]
        ]
      ]
    },
    "A"
  ], 
  "D": 3.141592653589793, 
  "E": false, 
  "F": 127, 
  "G": "0x0202"
}
*/
static const uint8_t binson_bytes[104] = "\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x40\x14\x01\x41\x14\x01\x42\x41\x14\x01\x43\x42\x14\x01\x41\x14\x01\x41\x40\x14\x01\x41\x14\x01\x42\x14\x01\x42\x42\x14\x01\x41\x14\x01\x41\x40\x14\x01\x41\x14\x01\x42\x41\x42\x42\x42\x42\x40\x14\x01\x41\x14\x01\x42\x41\x43\x43\x43\x43\x43\x41\x14\x01\x41\x43\x14\x01\x44\x46\x18\x2d\x44\x54\xfb\x21\x09\x40\x14\x01\x45\x45\x14\x01\x46\x10\x7f\x14\x01\x47\x18\x02\x02\x02\x41";


/*======= Test cases ========================================================*/

TEST(print_binson)
{
    binson_parser p;
    char buffer_print[512];
    int out_pipe[2];
    int saved_stdout;
    saved_stdout = dup(STDOUT_FILENO);  /* save stdout for display later */
    if( pipe(out_pipe) != 0 ) { /* make a pipe */
        printf("...\r\n");
        exit(1);
    }
    dup2(out_pipe[1], STDOUT_FILENO);   /* redirect stdout to the pipe */
    close(out_pipe[1]);
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));
    ASSERT_TRUE(binson_parser_print(&p));
    fflush(stdout);
    size_t printed_size = read(out_pipe[0], buffer_print, sizeof(buffer_print));
    dup2(saved_stdout, STDOUT_FILENO);
    /* Expected:
     * {"A":"B","B":{"A":"B"},"C":["A","A",{"A":"B","B":["A","A",{"A":"B"},[[[[{"A":"B"}]]]]]},"A"],"D":3.141593,"E":false,"F":127,"G":"0x0202"}
     * Actual:
     * {"A":"B","B":{"A":"B"},"C":["A","A",{"A":"B","B":["A","A",{"A":"B"},[[[[{"A":"B"}]]]]]},"A"],"D":3.141593,"E":false,"F":127,"G":"0x0202"}
     */
    char buffer[512];
    size_t size = sizeof(buffer);
    ASSERT_TRUE(binson_parser_to_string(&p, buffer, &size, false));
    ASSERT_TRUE(size == printed_size);
    ASSERT_TRUE(memcmp(buffer, buffer_print, size) == 0);
}

TEST(to_string_should_give_required_size)
{
    binson_parser p;
    binson_parser_init(&p, binson_bytes, sizeof(binson_bytes));

    char buffer[512];
    size_t size = sizeof(buffer);
    ASSERT_TRUE(binson_parser_to_string(&p, buffer, &size, false));

    size_t required_size = 0;
    ASSERT_TRUE(binson_parser_to_string(&p, NULL, &required_size, false));
    ASSERT_TRUE(size ==  required_size);
    char *new_buffer = malloc(required_size);
    ASSERT_TRUE(binson_parser_to_string(&p, new_buffer, &required_size, false));
    free(new_buffer);

}

/*======= Main function =====================================================*/

int main(void) {
    RUN_TEST(print_binson);
    RUN_TEST(to_string_should_give_required_size);
    PRINT_RESULT();
}

/*======= Local function implementations ====================================*/

