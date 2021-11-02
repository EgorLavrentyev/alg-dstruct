#include "memallocator.h"
#include "stdlib.h"

typedef struct descriptor_t {
    int size;
    struct descriptor_t* next;
    struct descriptor_t* prev;
    int isFree;   // 1 - free, 0 - busy
} descriptor_t;

static struct {
    descriptor_t* head;
    int fullsize;
} memlist = { (descriptor_t*)NULL, 0 };

int meminit(void* pMemory, int size)
{
    if(!pMemory || size <= memgetminimumsize())
    {
        return 0;
    }
    else
    {
        memlist.head = (descriptor_t*)pMemory;
        memlist.head->next = NULL;
        memlist.head->prev = NULL;
        memlist.head->size = size - memgetblocksize();
        memlist.head->isFree = 1;
        memlist.fullsize = size;
    }
    return 1;
}

void* memalloc(int size)
{
    void* ptr = NULL;
    descriptor_t* tmp;
    int descrsize = memgetblocksize();
    if (size <= 0 || memlist.head == NULL)
    {
        return NULL;
    }

    tmp = memlist.head;

    while (!((tmp->isFree == 1) && (tmp->size >= size)))
    {
        if (!tmp->next)
        {
            return NULL;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    if (tmp->size > size + descrsize) //if size of found block > required size
    {
        //describing right block
        descriptor_t* right = (descriptor_t*)((char*)tmp + size + descrsize);
        right->size = tmp->size - descrsize - size;
        right->next = tmp->next;
        right->prev = tmp;
        right->isFree = 1;

        if (tmp->next)
        {
            tmp->next->prev = right;
        }

        //describing left block

        tmp->size = size;
        tmp->next = right;
        tmp->isFree = 0;
    }
    else
    {
        tmp->isFree = 0;
    }
    ptr = (void*)((char*)tmp + descrsize);

    return ptr;
}

void memfree(void* p)
{
    descriptor_t* free_p = NULL;
    descriptor_t* tmp = NULL; //using this pointer if it is possible to merge 2 free blocks into 1
    int descrsize = memgetblocksize();

    if (p && memlist.head)
    {
        free_p = (descriptor_t*)((char*)p - descrsize);

        if (free_p >= memlist.head && free_p <= memlist.head + memlist.fullsize && !(free_p->isFree)) //if block was taken from our memory list
        {
            free_p->isFree = 1;

            if (free_p->next && free_p->next->isFree) //if it is possible to merge with right block:
            {
                //describing new "big" block
                tmp = free_p; //pointer to left block
                tmp->size = descrsize + tmp->size + tmp->next->size;

                if (tmp->next->next)
                {
                    tmp->next->next->prev = tmp;
                    tmp->next = tmp->next->next;
                }
                else
                {
                    tmp->next = NULL;
                }

                if (tmp->prev)
                {
                    tmp->prev->next = tmp;
                }
                else
                {
                    tmp->prev = NULL;
                }
            }

            if (free_p->prev && free_p->prev->isFree) //if it is possible to merge with left block:
            {

                tmp = free_p->prev;
                if (tmp->next)
                {
                    tmp->size = descrsize + tmp->size + tmp->next->size;
                }

                if (tmp->next)
                {
                    if (tmp->next->next)
                    {
                        tmp->next->next->prev = tmp;
                        tmp->next = tmp->next->next;
                    }
                    else
                    {
                        tmp->next = NULL;
                    }
                }

            }
        }
    }
}

void memdone()
{
    descriptor_t* cur = memlist.head;
    int memsum = 0;
    
    while (cur)
    {
        if (cur->isFree)
        {
            memsum += cur->size;
        }
        cur = cur->next;
    }
}

int memgetminimumsize() {
    return sizeof(descriptor_t);
}

int memgetblocksize() {
    return sizeof(descriptor_t);
}