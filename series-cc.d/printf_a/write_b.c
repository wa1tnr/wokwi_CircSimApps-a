/* Tue 28 Dec 03:16:49 UTC 2021 */

/* write and friends */

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h> // strlen only

void space_it(void) {
    printf("%c", ' ');
}

void newline(void) {
    printf("%c", '\n');
}

int main(void) {
    newline();
    char buffer[32];
    char* buf_ptr;

    /* ssize_t write(int fd, const void *buf, size_t count); */

    buffer[0] = 'a';
    buffer[1] = 'b';
    buffer[2] = 'c';
    buffer[3] = '\000';

    buf_ptr = buffer;


    int buf_size, buf_ptr_size;

    buf_size = sizeof(buffer); // captures "abc\000" size
    buf_ptr_size = sizeof(buf_ptr);

    int buf_len = strlen(buffer);

    ssize_t gottem;

    printf("%s ", "is the buffer contents");

    gottem = write(1, buf_ptr, sizeof(buf_ptr));

    sprintf(buf_ptr, "\n           sizeof(buf_ptr) is  %d", buf_ptr_size);
    printf(buf_ptr);

    printf("%s", "\n           sizeof(buffer)  is ");
    sprintf(buf_ptr, "%d\n", buf_size); // related to string length, possibly
    printf(buf_ptr);

    printf("%s", "           strlen(buffer)  is ");
// ##bookmark
    sprintf(buf_ptr, " %d\n", buf_len); // related to string length, possibly
    printf(buf_ptr);

    uint64_t adrs;
    adrs = (uint64_t) & buf_ptr;

    printf("%s", "adrs (& buf_ptr) in hex is      ");
    // print the buffer's address in ram
    sprintf(buf_ptr, "0x%.8X", adrs);
    printf(buf_ptr);

    printf("%s", "\nadrs (& buf_ptr) in decimal is ");
    sprintf(buf_ptr, "%.11u\n\n", adrs);

    printf(buf_ptr);
}

#if 0
   #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);
    
#endif

