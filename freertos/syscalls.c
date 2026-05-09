#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>

extern uint8_t _end;      // defined by linker
extern uint8_t _estack;   // defined by linker script / startup

static uint8_t *heap_end;

void *_sbrk(ptrdiff_t incr) {
    if (heap_end == 0) {
        heap_end = &_end;
    }

    uint8_t *prev_heap_end = heap_end;
    uint8_t *next_heap_end = heap_end + incr;

    if (next_heap_end >= &_estack) {
        errno = ENOMEM;
        return (void *)-1;
    }

    heap_end = next_heap_end;
    return prev_heap_end;
}

int _write(int file, char *ptr, int len) {
    (void)file;
    (void)ptr;
    return len;
}

int _close(int file) {
    (void)file;
    return -1;
}

int _fstat(int file, struct stat *st) {
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    (void)file;
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

int _read(int file, char *ptr, int len) {
    (void)file;
    (void)ptr;
    (void)len;
    return 0;
}

void _exit(int status) {
    (void)status;
    while (1) {}
}

int _kill(int pid, int sig) {
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

int _getpid(void) {
    return 1;
}