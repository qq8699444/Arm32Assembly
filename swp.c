#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>


struct mutex
{
    volatile  int32_t count;    
};


struct mutex gmutex = {0};
static int32_t cnt = 0;
static const int loopcnt = 1000*2000;


void spinlock(struct mutex* ptr)
{
    int32_t oldv = 0;
    int32_t newv = 1;
    do{
         asm volatile(               
            "swp %2, %1, [%0]    \n"
            :
            :"r"(ptr),
            "r"(newv),
            "r"(oldv)
            :"cc", "memory","r0"
        
        );
    
    }while(oldv != 0);
    assert(oldv == 0);
}

void spinunlock(struct mutex* ptr)
{
    int32_t oldv = 1;
    int32_t newv = 0;

    asm volatile(               
            "swp %2, %1, [%0]    \n"
            :
            :"r"(ptr),
            "r"(newv),
            "r"(oldv)
            :"cc", "memory","r0"
        
        );

    assert(oldv == 1);    
}

void* thread_entry(void* p)
{
    for (int  i = 0; i < loopcnt; i++)
    {
        spinlock(&gmutex);
        cnt++;
        spinunlock(&gmutex);
    }
    return NULL;
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    //printf("hello\n");
    pthread_t   tid1;
    pthread_t   tid2;
    pthread_create(&tid1,NULL,thread_entry,NULL);
    pthread_create(&tid2,NULL,thread_entry,NULL);

    //spinlock(&gmutex);
    //printf("mutex: %d\n", gmutex.count); 

    //spinunlock(&gmutex);
    //printf("mutex: %d\n", gmutex.count); 

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("cnt = %d\n",cnt);
    return 0;
}


