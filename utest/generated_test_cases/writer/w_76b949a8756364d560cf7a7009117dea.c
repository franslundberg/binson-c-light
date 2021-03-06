#include <assert.h>
#include <string.h>
#include "binson_writer.h"

/*
{
  "BBS1FFFFFFFFFFFFFFFFFFFFFFFFFFF3 d FFFFFFFFF F3  ?FFFFFF FFFFFFFFF??????FFF??????FF[?FFFF": 1.0347915464784313E10
}
*/
int main(void)
{
    uint8_t expected[163] = "\x40\x15\x95\x00\x42\x42\x53\x7f\x31\x12\x12\x12\x12\x12\x12\x12\x12\x16\x7f\x12\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x33\x14\x00\x14\x64\x00\x12\x1b\x46\x46\x46\x46\x46\x46\x46\x46\x46\x14\x01\x20\x46\x33\x14\x00\x14\x00\xef\xbf\xbd\x12\x1b\x46\x46\x46\x46\x46\x46\x7f\x00\x46\x46\x46\x46\x46\x46\x46\x46\x46\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xb5\x80\x3f\x46\x46\x46\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\x7f\xef\xbf\xbd\xef\xbf\xbd\x46\x14\x46\x5b\x3f\x46\x46\x46\x46\x46\x46\x46\x46\x46\x45\x46\x03\x42\x41";
    uint8_t created[163];
    binson_writer w;
    binson_writer_init(&w, created, sizeof(created));
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_begin(&w);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_name_with_len(&w, "\x42\x42\x53\x7f\x31\x12\x12\x12\x12\x12\x12\x12\x12\x16\x7f\x12\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x46\x33\x14\x00\x14\x64\x00\x12\x1b\x46\x46\x46\x46\x46\x46\x46\x46\x46\x14\x01\x20\x46\x33\x14\x00\x14\x00\xef\xbf\xbd\x12\x1b\x46\x46\x46\x46\x46\x46\x7f\x00\x46\x46\x46\x46\x46\x46\x46\x46\x46\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xb5\x80\x3f\x46\x46\x46\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\x7f\xef\xbf\xbd\xef\xbf\xbd\x46\x14\x46\x5b\x3f\x46\x46\x46\x46", 149);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_double(&w, 1.0347915464784313E10);
    assert(w.error_flags == BINSON_ID_OK);
    binson_write_object_end(&w);
    assert(w.error_flags == BINSON_ID_OK);
    assert(memcmp(expected, created, sizeof(expected)) == 0);
    return 0;
}

