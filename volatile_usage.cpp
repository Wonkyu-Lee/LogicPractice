//
// Created by blazeq on 2017. 11. 17..
//

namespace {

void func() {
    volatile int i = 0;
    int volatile j = 0;
    int k;

    // pointer to volatile int, not volatile pointer
    volatile int* p = &i;
    p = &j;
    p = &k;

    //int* volatile q = &i; // volatile pointer cannot point volatile variable
    int* volatile q = &k;
    // q = &i;

    volatile int* volatile r = &i;
}

} // namespace
