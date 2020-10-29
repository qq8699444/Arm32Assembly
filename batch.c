#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>



void test_batch()
{
    int32_t intArr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int32_t intArr2[16];
    int32_t intArr3[16];


    int32_t *ptr1= intArr1;
    int32_t *ptr2= intArr2-1;

    //
    asm volatile(
        "ldmia    %0,  {r0-r7}  \n"
        "stmib    %1,  {r0-r7}  \n"
        :
        :"r"(ptr1),
        "r"(ptr2)
        :"cc", "memory","r0","r1","r2","r3","r4","r5","r6","r7"
    );
    //printf("v: %#x\n", v);
    assert(ptr1 == intArr1);
    for (int i = 0; i <8;i++)
    {
        assert(intArr1[i] == intArr2[i]);
    }


    ptr1= intArr1 + 7;
    ptr2= intArr3 + 8;

    asm volatile(
        "ldmda    %0,  {r0-r7}  \n"
        "stmdb    %1,  {r0-r7}  \n"
        :
        :"r"(ptr1),
        "r"(ptr2)
        :"cc", "memory","r0","r1","r2","r3","r4","r5","r6","r7"
    );
    //printf("v: %#x\n", v);
    //assert(v == intArr[1]);
    for (int i = 0; i <8;i++)
    {
        //printf("intArr3[%d] = %d\n", i , intArr3[i]);
        assert(intArr1[i] == intArr3[i]);
    }

}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    test_batch();

    printf("all ok!\n");
    return 0;
}


