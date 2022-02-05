/* Tue 28 Dec 01:52:47 UTC 2021 */

/* sprintf and friends */

#include <stdio.h>

int main(void) {
    char buffer[20];
    char* buf_ptr;
    buf_ptr = buffer;
    sprintf(buf_ptr, "%s", "hello");
    printf(buffer);
}
