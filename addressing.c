#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

void test_Addressing_mode()
{
    int i = rand() & 0xffff;
    int32_t ret1;
    asm volatile(
        "mov %0,    #0xff          \n"
        :"=r"(ret1)
        :
        :"cc", "memory"
    );
    //printf("immediate mode: %#x\n", ret1); 
    assert(ret1 == 0xff);


    int32_t ret2;
    asm volatile(
        "mov r0,    %1          \n"
        "mov %0,    r0          \n"
        :"=r"(ret2)
        :"r"(i)
        :"cc", "memory","r0"
    );
    //printf("reg mode: %#x\n", ret2); 
    assert(ret2 == i);

    int32_t ret3;
    asm volatile(
        "mov r0,    %1          \n"
        "mov %1,    r0 ,LSL #4         \n"
        :"=r"(ret3)
        :"r"(i)
        :"cc", "memory","r0"
    );
    //printf("LSL mode: %#x\n", ret3); 
    assert(ret3 == i*16);

    int32_t ret4;
    asm volatile(
        "mov r0,    #4          \n"
        "mov %0,    %1 ,LSL r0  \n"
        :"=r"(ret4)
        :"r"(i)
        :"cc", "memory","r0"
    );
    //printf("LSL mode: %#x\n", ret4); 
    assert(ret4 == i*16);

    // LSR
    i = 0xfff;
    int32_t ret5;
    asm volatile(
        "mov r0,    %0          \n"
        "mov %1,    r0 ,LSR #4         \n"
        :"=r"(ret5)
        :"r"(i)
        :"cc", "memory","r0"
    );
    //printf("LSR mode: %#x\n", ret5); 
    assert(ret5 == i/16);

    int32_t ret6;
    asm volatile(
        "mov r0,    #4          \n"
        "mov %0,    %1 ,LSR r0  \n"
        :"=r"(ret6)
        :"r"(i)
        :"cc", "memory","r0"
    );
    //printf("LSR mode: %#x\n", ret6); 
    assert(ret6 == i/16);

    // ASR
    i = 0x80000ff0;
    int32_t ret7;
    int32_t ret8;
    asm volatile(
        "mov r0,    #4          \n"
        "mov %0,    %2 ,ASR #4         \n"
        "mov %1,    %2 ,ASR r0  \n"
        :"=r"(ret7),
        "=r"(ret8)
        :"r"(i)
        :"cc", "memory","r0"
    );
    //printf("ASR mode: %d, %d,%d\n", i, ret7, ret8); 
    assert(ret7 == i/16);
    assert(ret8 == i/16);

    int32_t ret11;
    int32_t ret12;
    i = 0x0000ffff;
    asm volatile(
        "mov r0,    #4          \n"
        "mov %0,    %2 ,ROR #4         \n"
        "mov %1,    %2 ,ROR r0  \n"
        :"=r"(ret11),
        "=r"(ret12)
        :"r"(i)
        :"cc", "memory","r0"
    );
    //printf("ROR mode: %#x, %#x,%#x\n", i, ret11, ret11); 
    assert(ret11 == 0xf0000fff);
    assert(ret12 == 0xf0000fff);

    int32_t ret9;
    i = 0x0000ffff;
    asm volatile(
        
        "RRX %0,    %1         \n"
        "adc %0, %0, #0         \n"
        :"=r"(ret9)
        :"r"(i)
        :"cc", "memory"
    );
    //printf("RRX mode: %#x\n", ret9); 
    assert((ret9 & 0xffff) == 0x8000);
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_Addressing_mode();
    
    printf("all ok!\n");
    return 0;
}
