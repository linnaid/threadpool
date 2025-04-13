#include <iostream>
#include "lock.h"
#include <mutex>

using namespace std;


//初始化 lock_t 结构
void amountInit(lock_t* Account) {
    Account->amount = 0;
    Account->mutex = PTHREAD_MUTEX_INITIALIZER;
}

//用于进行资金收入操作，金额为 amount
void Income(lock_t* Account, int amount) {
    if(pthread_mutex_trylock(&Account->mutex) == 0)
    {
        Account->amount += amount;

        pthread_mutex_unlock(&Account->mutex);
    }
    else
    {
        pthread_mutex_lock(&Account->mutex);
        Account->amount += amount;
        pthread_mutex_unlock(&Account->mutex);
    }
}

//用于进行资金支出操作，金额为 amount
void Expend(lock_t* Account, int amount) {
    if(pthread_mutex_trylock(&Account->mutex) == 0)
    {
        Account->amount -= amount;
        pthread_mutex_unlock(&Account->mutex);
    }
    else
    {
        pthread_mutex_lock(&Account->mutex);

        Account->amount -= amount;
        pthread_mutex_unlock(&Account->mutex);
    }
}

