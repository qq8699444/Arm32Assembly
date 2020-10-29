#include <cstdio>
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <vector>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <chrono>
//#include <arm_neon.h>


#define N 10240

void bsort(int* arr, const int n)
{
    for (int c = 0 ; c < n - 1; c++)
    {
        for (int d = 0 ; d < n - c - 1; d++)
        {
            if (arr[d] > arr[d+1]) /* For decreasing order use '<' instead of '>' */
            {
            auto swap       = arr[d];
            arr[d]   = arr[d+1];
            arr[d+1] = swap;
            }
        }
    }

}


void bsortAsm(int* arr, const int len)
{
    asm volatile(
        "sub r2, %1,#1      \n"
        "mov r3, #0  //i    \n"
        "2:             \n"
        "cmp  r3, r2        \n"
        "beq  1f            \n"
        "add  r3, #1        \n"
        "add  r4, %0, r2, LSL #2  //end   \n"
        "mov  r5, %0 //&arr[j]     \n"
        "ldr  r7, [r5] //arr[j]     \n"
        "3:                 \n"
        "cmp  r4, r5        \n"
        "beq 2b             \n"
        "ldr r6, [r5, #4]   \n"
        "cmp   r7, r6       \n"
        "stmgt  r5, {r6,r7} \n"
        "movle  r7, r6      \n"
        "add r5,  r5, #4    \n"
        "b 3b               \n"
        "1:                 \n"
        :"+r"(arr)        // %0

        :"r"(len)         // %1
        : "cc", "memory", "r0", "r1","r2","r3","r4","r5","r6","r7"
    );
}


int main(int argc, char** argv) {
        printf("main ++!\n\n");
    srand(time(NULL));
    int*  data1 = new int[N];
    int*  data2 = new int[N];


    for (int i = 0; i < N;i++)
        data1[i] = data2[i] = rand()&0xff;

    for (int i = 0; i < N;i++)
    {
        //printf("%d\t",data1[i]);
    }
    printf("\n");
    for (int i = 0; i < N;i++)
    {
        //printf("%d\t",data2[i]);
    }
    printf("\n");

    {
        auto start =  std::chrono::high_resolution_clock::now();
        bsort(data1, N);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> delta_us = end - start;
        double ctime  = delta_us.count();
        printf("ctime %f --!\n\n", ctime);
    }


#if 1
    {
        auto start =  std::chrono::high_resolution_clock::now();
        bsortAsm(data2, N);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> delta_us = end - start;
        double asmtime  = delta_us.count();
        printf("asm time %f --!\n\n", asmtime);
    }
#endif

    for (int i = 0; i < N;i++)
    {
        //printf("%d\t",data1[i]);
    }
    printf("\n");
    for (int i = 0; i < N;i++)
    {
        //printf("%d\t",data2[i]);
    }
    printf("\n");


    for (int i = 0; i < N;i++)
    {
        if (data1[i] != data2[i])
        {
            printf(" error at %d %d %d --!\n\n", i, data1[i] , data2[i]);
            break;
        }
    }




    printf("main --!\n\n");

    return 0;
}
