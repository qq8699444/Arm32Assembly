#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_ldr_str()
{
    int32_t intArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int32_t *ptr= intArr;
    int32_t v;

    // 1
    asm volatile(       
        "ldr %0,    [%1,#4]  \n"
        :"=r"(v)
        :"r"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[1]);


    // 2
    v = rand();
    asm volatile(     
        "mov r0,    #8       \n"  
        "ldr %0,    [%1,r0]  \n"
        :"=r"(v)
        :"r"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[2]);


    // 3
    v = rand();
    asm volatile(     
        "mov r0,    #2       \n"  
        "ldr %0,    [%1,r0,LSL #2]  \n"
        :"=r"(v)
        :"r"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[2]);


    // 4
    v = rand();
    asm volatile(       
        "ldr %0,    [%1,#4]!  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[1]);
    assert(ptr-1 == intArr);

    // 5
    ptr= intArr;v = rand();
    asm volatile(     
        "mov r0,    #8        \n"    
        "ldr %0,    [%1,r0]!  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    assert(v == intArr[2]);
    assert(ptr-2 == intArr);


    // 6
    ptr= intArr;v = rand();
    asm volatile(     
        "mov r0,    #2        \n"    
        "ldr %0,    [%1,r0,LSL #2]!  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    assert(v == intArr[2]);
    assert(ptr-2 == intArr);


    // 7
    ptr= intArr;v = rand();
    v = rand();
    asm volatile(       
        "ldr %0,    [%1],#8  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[0]);
    assert(ptr-2 == intArr);

    //  8 
    ptr= intArr;v = rand();
    v = rand();
    asm volatile(   
        "mov r0,    #8        \n"        
        "ldr %0,    [%1],r0  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[0]);
    assert(ptr-2 == intArr);

    //  9 
    ptr= intArr;v = rand();
    v = rand();
    asm volatile(   
        "mov r0,    #2        \n"        
        "ldr %0,    [%1],r0,LSL #2  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[0]);
    assert(ptr-2 == intArr);

}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_ldr_str();
    
    printf("all ok!\n");
    return 0;
}


