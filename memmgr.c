#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_mrc()
{
    
    int32_t v = 0;
    asm volatile(               
        "mrc p15,  0,  %0, c1,  c0, 0 \n"
        :
        :"r"(v)
        :"cc", "memory","r0"
    );
    printf("v: %d\n", v); 
    //assert(v == 3*8);


 
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_mrc();
    
    printf("all ok!\n");
    return 0;
}


