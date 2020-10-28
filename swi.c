#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_swi()
{
   
    int32_t v = 0;
    asm volatile(               
        "mov %0, %0 \n"
        "mov r7, #1 \n"
        "swi  #0       \n"
        :
        :"r"(v)
        :"cc", "memory","r0"
    );
    printf("never see this\n");  
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_swi();
    
    
    return 0;
}


