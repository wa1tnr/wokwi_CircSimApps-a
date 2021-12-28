/* Tue 28 Dec 03:16:49 UTC 2021 */

/* write and friends */

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

void space_it(void) {
    printf("%c", ' ');
}

void newline(void) {
    printf("%c", '\n');
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


    newline();
    gottem = write(1, buf_ptr, sizeof(buf_ptr));

    sprintf(buf_ptr, "\n\n%d", gottem);
    printf(buf_ptr);

    uint64_t adrs;
    adrs = (uint64_t) & buf_ptr;

    // sprintf(buf_ptr, "\n  %.12X", adrs);
    sprintf(buf_ptr, "\n     %.8X", adrs);
    space_it();

    printf(buf_ptr);
    // sprintf(buf_ptr, "\n  %.16u\n\n", adrs);
    sprintf(buf_ptr, "\n  %.11u\n\n", adrs);

    space_it();
    printf(buf_ptr);
}

#if 0
   #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);
    
#endif

