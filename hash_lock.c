#include "hash_lock.h"

#include <stdio.h>
#include <stdlib.h>

//初始化哈希桶 bucket，为它设置初始状态
//初始化哈希桶、锁
void hashInit(hash_lock_t* bucket) {
    for(int i = 0; i < HASHNUM; i++)
    {
        int n = pthread_mutex_init(&bucket->table[i].mutex, NULL);
        if(n != 0)
        {
          perror("Mutex initialization failed");
          exit(EXIT_FAILURE);
        }
        bucket->table[i].head = NULL;
    }
}

//查找 key 对应的 value 并返回。这个是典型的哈希查找操作。
//获取 key 对应的值
int getValue(hash_lock_t* bucket, int key) {
    int num = HASH(key);
    pthread_mutex_lock(&bucket->table[num].mutex);

    if(bucket->table[num].head == NULL)
    {
        pthread_mutex_unlock(&bucket->table[num].mutex);
        return 0;
    }
    Hnode* a = bucket->table[num].head;
    while(a != NULL)
    {
      if(a->key == key)
      {
          pthread_mutex_unlock(&bucket->table[num].mutex);
          return a->value;
      }
      a = a->next;
    }

    pthread_mutex_unlock(&bucket->table[num].mutex);
    return 0;
}

//向哈希桶中插入一个新节点（key-value)
void insert(hash_lock_t* bucket, int key, int value) {
    int num = HASH(key);
    pthread_mutex_lock(&bucket->table[num].mutex);

    Hnode* b = (Hnode*)malloc(sizeof(Hnode));
    b->key = key;
    b->value = value;
    b->next = NULL;
    
    if(bucket->table[num].head == NULL)
    {
        bucket->table[num].head = b;
    }
    else
    {
        Hnode* a = bucket->table[num].head;

        while(a->next != NULL)
        {
          if(a->key == key)
          {
            a->value = value;
            free(b);
            pthread_mutex_unlock(&bucket->table[num].mutex);
            return;
          }
            a = a->next;
        }
        
        a->next = b;
    }
    

    pthread_mutex_unlock(&bucket->table[num].mutex);
}

//找到 key，并把它改成 new_key。
//修改 key 的值
int setKey(hash_lock_t* bucket, int key, int new_key) {
    int num = HASH(key);
    pthread_mutex_lock(&bucket->table[num].mutex);

    if(bucket->table[num].head == NULL)
    {
        pthread_mutex_unlock(&bucket->table[num].mutex);
        return -1;
    }
    else
    {
      Hnode* a = bucket->table[num].head;

      while(a != NULL)
      {
        if(a->key == key)
        {
          a->key = new_key;
          pthread_mutex_unlock(&bucket->table[num].mutex);
          return 0;
        }
        a = a->next;
      }
    }

    pthread_mutex_unlock(&bucket->table[num].mutex);
    return -1;
}
