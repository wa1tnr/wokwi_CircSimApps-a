/* Tue 28 Dec 02:14:27 UTC 2021 */

/* write and friends */

#include <stdio.h>
#include <unistd.h>

void space_it(void) {
    printf("%c", ' ');
}

int main(void) {
    char buffer[20];

    char* buf_ptr, buf_buf_ptr;

    buf_ptr = buffer;

    /* ssize_t write(int fd, const void *buf, size_t count); */
    ssize_t gottem;

    buffer[0] = 'a';
    buffer[1] = 'b';
    buffer[2] = 'c';
    buffer[3] = '\000';
    gottem = write(1, buf_ptr, sizeof(buf_ptr));

    sprintf(buf_ptr, "%d", gottem);

    space_it();

    printf(buf_ptr);
    space_it();

    long int adrs;
    adrs = (long int) & buf_ptr;
    printf("%d\n", adrs);
    // printf("%c", ' ');

}

#if 0
   #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);
    
#endif

