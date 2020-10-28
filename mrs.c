#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_mrs()
{
    
    int32_t v = 0;
    int32_t v2 = 0;
    asm volatile(               
        "mrs %0, cpsr \n"
        :"=r"(v)
        :
        :"cc", "memory","r0"
    );
    printf("v: %#x\n", v);  

    v &= 0x00ffffff;
    asm volatile(               
        "msr cpsr, %1 \n"
        "mrs %0, cpsr \n"
        :"=r"(v2)
        :"r"(v)
        :"cc", "memory","r0"
    );
    printf("v: %#x\n", v2);  

}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_mrs();
    
    printf("all ok!\n");
    return 0;
}


