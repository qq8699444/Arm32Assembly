#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_jump()
{
    int32_t v = 0;
    asm volatile(               
        "b 1f               \n"
        "add %0, #1          \n"
        "1:                 \n"
        :"=r"(v)
        :
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 0);


    asm volatile(               
        "bl 1f               \n"        
        "1:                 \n"
        "sub %0, pc,lr          \n"
        :"=r"(v)
        :
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 8);
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_jump();
    
    printf("all ok!\n");
    return 0;
}


