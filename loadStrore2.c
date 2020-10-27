#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_ldr_byte()
{
    int8_t intArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int8_t *ptr= intArr;
    int8_t v;

    // 1
    asm volatile(       
        "ldrsb %0,    [%1,#1]  \n"
        :"=r"(v)
        :"r"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[1]);


    // 2
    v = rand();
    asm volatile(     
        "mov r0,    #2       \n"  
        "ldrsb %0,    [%1,r0]  \n"
        :"=r"(v)
        :"r"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[2]);


    // 3
    v = rand();
    asm volatile(       
        "ldrsb %0,    [%1,#4]!  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[4]);
    assert(ptr-4 == intArr);

    // 5
    ptr= intArr;v = rand();
    asm volatile(     
        "mov r0,    #8        \n"    
        "ldrsb %0,    [%1,r0]!  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    assert(v == intArr[8]);
    assert(ptr-8 == intArr);


    // 7
    ptr= intArr;v = rand();
    v = rand();
    asm volatile(       
        "ldrsb %0,    [%1],#8  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[0]);
    assert(ptr-8 == intArr);

    //  8 
    ptr= intArr;v = rand();
    v = rand();
    asm volatile(   
        "mov r0,    #8        \n"        
        "ldrsb %0,    [%1], r0  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[0]);
    assert(ptr-8 == intArr);

   
}


void test_ldr_word()
{
    int16_t intArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int16_t *ptr= intArr;
    int16_t v;

    // 1
    asm volatile(       
        "ldrh %0,    [%1,#2]  \n"
        :"=r"(v)
        :"r"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[1]);


    // 2
    v = rand();
    asm volatile(     
        "mov r0,    #4       \n"  
        "ldrh %0,    [%1,r0]  \n"
        :"=r"(v)
        :"r"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[2]);


    // 3
    v = rand();
    asm volatile(       
        "ldrh %0,    [%1,#8]!  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[4]);
    assert(ptr-4 == intArr);

    // 5
    ptr= intArr;v = rand();
    asm volatile(     
        "mov r0,    #8        \n"    
        "ldrh %0,    [%1,r0]!  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    assert(v == intArr[4]);
    assert(ptr-4 == intArr);


    // 7
    ptr= intArr;v = rand();
    v = rand();
    asm volatile(       
        "ldrh %0,    [%1],#8  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[0]);
    assert(ptr-4 == intArr);

    //  8 
    ptr= intArr;v = rand();
    v = rand();
    asm volatile(   
        "mov r0,    #8        \n"        
        "ldrh %0,    [%1], r0  \n"
        :"=r"(v),
        "=r"(ptr)
        :"1"(ptr)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == intArr[0]);
    assert(ptr-4 == intArr);

   
}


int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_ldr_byte();
    test_ldr_word();
    
    printf("all ok!\n");
    return 0;
}


