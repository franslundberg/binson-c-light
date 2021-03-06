#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "BBCF??      BBBBBBFF?FFFFFFFFF": 1.0347915464784313E10
}
*/
int main(void)
{
    uint8_t expected[49] = "\x40\x14\x24\x42\x42\x43\x46\xef\xbf\xbd\xef\xbf\xbd\x00\x00\x00\x00\x00\x00\x42\x42\x42\x42\x42\x42\x46\x46\xef\xbf\xbd\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x45\x46\x03\x42\x41";
    uint8_t created[49];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x42\x42\x43\x46\xef\xbf\xbd\xef\xbf\xbd\x00\x00\x00\x00\x00\x00\x42\x42\x42\x42\x42\x42\x46\x46\xef\xbf\xbd\x46\x46\x46\x46\x46\x46\x46\x46\x46", 36);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_double(&w, 1.0347915464784313E10);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

