/* Tue 28 Dec 02:51:05 UTC 2021 */

/* write and friends */

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

void space_it(void) {
    printf("%c", ' ');
}

int main(void) {
    char buffer[20];
    char* buf_ptr, buf_buf_ptr;

    /* ssize_t write(int fd, const void *buf, size_t count); */

    buffer[0] = 'a';
    buffer[1] = 'b';
    buffer[2] = 'c';
    buffer[3] = '\000';

    buf_ptr = buffer;

    ssize_t gottem;

    gottem = write(1, buf_ptr, sizeof(buf_ptr));
    space_it();

    sprintf(buf_ptr, "%d", gottem);
    printf(buf_ptr);
    space_it();

    uint64_t adrs;
    adrs = (uint64_t) & buf_ptr;

    sprintf(buf_ptr, "%.12X", adrs);
    space_it();

    printf(buf_ptr);
    sprintf(buf_ptr, "%.16d", adrs);

    space_it();
    printf(buf_ptr);
}

#if 0
   #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);
    
#endif

