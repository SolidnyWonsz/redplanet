extern "C" {

void *__dso_handle = nullptr;

struct {
    void (*destructor)(void*);
    void *arg;
    void *dso;
} __atexit_func_entry_t[128];

unsigned __atexit_func_count = 0;

int __cxa_atexit(void (*destructor)(void*), void *arg, void *dso) {
    if (__atexit_func_count >= 128) {
        return -1;
    }
    __atexit_func_entry_t[__atexit_func_count].destructor = destructor;
    __atexit_func_entry_t[__atexit_func_count].arg = arg;
    __atexit_func_entry_t[__atexit_func_count].dso = dso;
    __atexit_func_count++;
    return 0;
}

void __cxa_finalize(void *f) {
    unsigned i = __atexit_func_count;
    if (!f) {
        while (i--) {
            if (__atexit_func_entry_t[i].destructor) {
                (*__atexit_func_entry_t[i].destructor)(__atexit_func_entry_t[i].arg);
            }
        }
        return;
    }

    while (i--) {
        if (__atexit_func_entry_t[i].destructor == f) {
            (*__atexit_func_entry_t[i].destructor)(__atexit_func_entry_t[i].arg);
            __atexit_func_entry_t[i].destructor = 0;
        }
    }
}

}