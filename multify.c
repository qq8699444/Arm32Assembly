#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


void test_mul()
{
    int32_t a = 0xffff;
    int32_t b = 0x10;

    int32_t v = 10;
    asm volatile(               
        "mul %0,    %1, %2  \n"
        :"+r"(v)
        :
         "r"(a),
         "r"(b)
        :"cc", "memory"
    );
    //printf("v: %#x\n", v); 
    assert(v == a*b);

    // mla
    v = 0xf;
    asm volatile(               
        "mla %0,   %1, %2, %0  \n"
        :"+r"(v)
        :
         "r"(a),
         "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x\n", v); 
    assert(v == a*b+0xf);
    

    // smull
    a = 0x7fffffff;
    b = 0x100;
    int32_t v2;
    asm volatile(               
        "smull %0,%1,   %2, %3  \n"
        :"+r"(v),
         "+r"(v2)
        :
         "r"(a),
         "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x, %#x\n", v,v2); 
    assert(v == 0xffffff00);
    assert(v2 == 0x7f);

    // smlal
    a = 0x7fffffff;
    b = 0x100;
    v = 0xff;
    v2 = 0x80;
    
    asm volatile(               
        "smlal %0,%1,   %2, %3  \n"
        :"+r"(v),
         "+r"(v2)
        :
         "r"(a),
         "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x, %#x\n", v,v2); 
    assert(v == 0xffffffff);
    assert(v2 == 0xff);

    //umull
    a = 0xffffffff;
    b = 0x100;
    asm volatile(               
        "umull %0,%1,   %2, %3  \n"
        :"+r"(v),
         "+r"(v2)
        :
         "r"(a),
         "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x, %#x\n", v,v2); 
    assert(v == 0xffffff00);
    assert(v2 == 0xff);


    //umlal
    a = 0xffffffff;
    b = 0x100;
    v = 0xff;
    v2 = 0xf00;
    
    asm volatile(               
        "umlal %0,%1,   %2, %3  \n"
        :"+r"(v),
         "+r"(v2)
        :
         "r"(a),
         "r"(b)
        :"cc", "memory","r0"
    );
    //printf("v: %#x, %#x\n", v,v2); 
    assert(v == 0xffffffff);
    assert(v2 == 0xfff);
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_mul();
    
    printf("all ok!\n");
    return 0;
}


