#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_mov()
{
    int32_t v = 0;
    asm volatile(        
        "mov %0, #1          \n"        
        :"=r"(v)
        :
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 1);


    asm volatile(               
       "mov  r0, #2               \n"        
       "mov  %0, r0                 \n"     
        :"=r"(v)
        :
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 2);


    asm volatile(               
       "mov  r0, #2               \n"        
       "mov  %0, r0,LSR #1                 \n"     
        :"=r"(v)
        :
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 1);

}


void test_movn()
{
    int32_t v = 0;
    asm volatile(        
        "mvn %0, #0x3f          \n"        
        :"=r"(v)
        :
        :"cc", "memory","r0"
    );
    //printf("v: %d\n", v); 
    assert(v == ~0x3f);
}

void test_add()
{
    uint32_t ah = 3;
    uint32_t al = 0xffffffff;

    uint32_t bh = 5;
    uint32_t bl = 0xfffffffe;

    uint32_t vh = 0;
    uint32_t vl = 0;
    asm volatile(        
        "adds %1, %3, %5          \n"  
        "adc  %0, %4, %2          \n"             
        :"+r"(vh),      //0
         "+r"(vl)   
        :
        "r"(ah),       //2
         "r"(al), 
         "r"(bh),       //4
         "r"(bl) 
        :"cc", "memory","r0","r1","r2","r3"
    );
    printf("v: %#x %3x\n", vh, vl); 
    assert(vh == 9);
}


void test_sub()
{
    int32_t loop = 10;
    int32_t v = 1;
    asm volatile(   
        "1:                       \n"   
        "subs %0, %0, #1          \n"
        "movne %1, %1,  LSL #1     \n"   
        "bne   1b                  \n"   

        
        :"=r"(loop),
        "=r"(v)
        :"0"(loop),
        "1"(v)
        :"cc", "memory","r0"
    );
    //printf("v: %d\n", v); 
    assert(v == 512);
    assert(loop == 0);
}


void test_bit()
{
    int32_t a = 0xfff0;
    int32_t b = 0x00ff;

    int32_t v = 0;

    // and
    asm volatile(   
       
        "and   %0,  %1, %2                  \n"   

        
        :"=r"(v)
        :"r"(a),
        "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 0xf0);


    // or
    asm volatile( 
        "orr   %0,  %1, %2                  \n"         
        :"=r"(v)
        :"r"(a),
        "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 0xffff);


    // eor
    asm volatile( 
        "eor   %0,  %1, %2                  \n"         
        :"=r"(v)
        :"r"(a),
        "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 0xff0f);


    // bic
    asm volatile( 
        "bic   %0,  %1, %2                  \n"         
        :"=r"(v)
        :"r"(a),
        "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == 0xff00);

    // cmp
    v = 0x10;
    asm volatile( 
        "cmp     %1, %2                  \n"         
        "lsleq   %0, %0, #1"
        :"=r"(v)
        :"0"(v),
         "r"(a),
         "r"(b)
        :"cc", "memory","r0"
    );
    //printf("cmp v: %#x\n", v); 
    assert(v == 0x10);


    // tst
    v = 0x20;
    asm volatile( 
        "cmp     %1, #0x10                  \n"         
        "lsleq   %0, %0, #1"
        :"=r"(v)
        :"0"(v),
         "r"(a),
         "r"(b)
        :"cc", "memory","r0"
    );
    //printf("cmp v: %#x\n", v); 
    assert(v == 0x20);

    // teq
    v = 0x40;
    asm volatile( 
        "teq     %1, %2                  \n"         
        "lsleq   %0, %0, #1"
        :"=r"(v)
        :"0"(v),
         "r"(a),
         "r"(b)
        :"cc", "memory","r0"
    );
    //printf("cmp v: %#x\n", v); 
    assert(v == 0x40);
}
int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_mov();
    test_movn();

    test_add();
    test_sub();

    test_bit();
    
    printf("all ok!\n");
    return 0;
}


