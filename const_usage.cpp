//
// Created by blazeq on 2017. 11. 17..
//

namespace {

void func() {
    const int i = 0;
    int j = 1;
    int k = 2;

    // pointers
    {
        const int* p = &i;
        int const* p2 = &i; // same
        // *p = 5;
        p = &j;

        int* const q = &j;
        // int* const q2 = &i;
        *q = 5;
        // q = &k;

        const int* const r = &j;
        int const* const r2 = &j;
        // *ri = 5;
        // ri = &k;
        // *r2 = 5;
        // r2 = &k;
    }

    // references
    {
        const int& p = i;
        int const& p2 = i;
        // p = 5;
        // p2 = 5;
    }
}

} // namespace