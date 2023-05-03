//
// Created by sorliog on 4/8/2023.
//
#include "shared.h"
#include <iostream>
#include<ctime>
#include<unistd.h>

int main(int argc, char *args[]) {
    void *addrs = (void *) multiply;
    std::time_t time;
    printf("addrs: %p\n", addrs);
    int m = 2539; // Modding value
    int i = 7; // Initial i

    std::time_t start;
    start = std::time(0);

    while (std::time(0) - start <= 10) {
    	// Wait some time
        usleep(600000);
        time = std::time(0);
        if (i % 2 == 1) { // If odd, then multiply
            i = multiply(i, 363) % m;
            while(std::time(0) <= time){
                multiply(3,7);
            }
            time = std::time(0);
                printf("[%ld] multiply %d\n", time, i);
        } else { // else square, then multiply
            i = square(i) % m;

             while(std::time(0) <= time){
                 i = square(3);

             }
             time = std::time(0);
            printf("[%ld] square %d\n",time, i);
        }
    }

    return 0;
}
