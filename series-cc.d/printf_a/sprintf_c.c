/* Tue 28 Dec 01:52:47 UTC 2021 */

/* sprintf and friends */

#include <stdio.h>
// #include <unistd.h>
int main(void) {
    char buffer[20];
    char* buf_ptr;
    buf_ptr = buffer;

    // sprintf(buffer, "%s", "hello");

    // sprintf((char*)buffer, "%s", "hello");

    sprintf(buf_ptr, "%s", "hello");

    printf(buffer);
}
