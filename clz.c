#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_clz()
{
    int32_t a = 0xff;
    int32_t v = 0;
    asm volatile(               
        "clz %0, %1 \n"
        :"=r"(v)
        :"r"(a)
        :"cc", "memory","r0"
    );
    printf("v: %d\n", v); 
    assert(v == 3*8);


 
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_clz();
    
    printf("all ok!\n");
    return 0;
}


