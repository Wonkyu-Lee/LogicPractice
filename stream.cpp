//
// Created by blazeq on 2017. 11. 10..
//

#include <iostream>
#include "catch.hpp"

namespace {

TEST_CASE("Stream", "[stream]") {

//    {
//        // write
//        {
//            FILE* fp = fopen("stream.txt", "wt");
//            fputs("abc\ndef\n", fp);
//            fclose(fp);
//        }
//
//        // read
//        {
//            char buffer[256] = {0,};
//            FILE* fp = fopen("stream.txt", "rt");
//            fgets(buffer, 256, fp);
//            fclose(fp);
//        }
//    }

//    {
//        FILE* fp = nullptr;
//
//        fp = fopen("stream.txt", "wt");
//        fputs("abcdefg", fp);
//        fclose(fp);
//
//        fp = fopen("stream.txt", "rt");
//        char buffer[3] = {0,};
//        fgets(buffer, 3, fp);
//        fclose(fp);
//    }

//    SECTION("Read null-end string"){
//        FILE* fp = nullptr;
//
//        fp = fopen("stream.txt", "wb");
//        int arr[5] = {1, 2, 3, 4, 5};
//        fwrite(arr, sizeof(int), 5, fp);
//        fclose(fp);
//
//
//        fp = fopen("stream.txt", "rb");
//        int arr2[5] = {0,};
//        long p = 0;
//
//        for (int i = 0; i < 5; ++i) {
//            fread(arr2, sizeof(int), 1, fp);
//            p = ftell(fp);
//            printf("p = %ld\n", p);
//        }
//
//        fclose(fp);
//    }

    SECTION("stdin") {
        printf("Type a string(0 to end): ");
        char buffer[256];
        scanf("%s", buffer);
        printf("You typed '%s'\n", buffer);
    }

}

} // namespace