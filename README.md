# container
c container lib, include link list, squence list and hashtable.

### quick start
1. copy .h and .c files to your project
2. include .h file in your source code
3. use it like fowllowing
```
#include <stdlib.h>
#include <stdio.h>
#include "sqlist.h"

int main(int argc, char **argv)
{
    SqList l;
    SqListElement * e;
    void *temp;
    int  *v=NULL;

    init_SqList(&l);

    v = (int*)malloc(sizeof(int));
    *v = 9;
    pushBack_SqList(&l, v); //v is a point, all container save point to real data

    e = getFirst_SqList(&l);        
    printf("%d\n", *(int*)(e->value_point));  //value_point is void*, so we should transform it to int*

    temp = popBack_SqList(&l);
    free(temp);                 //here we freed temp, so we shouldn't free v again

    destroy_SqList(&l);

    return 0;
}

```

### details
you can take a look at test code, and header files has interface explaination.

### Link List
![image](https://github.com/ghking1/container/raw/master/doc/lklist.png)

### Sequence List
![image](https://github.com/ghking1/container/raw/master/doc/sqlist.png)

### HashTable
![image](https://github.com/ghking1/container/raw/master/doc/hashtable.png)

### something should take attention
* all data are saved as point in container, so the data must not local variable if you want to use it outly
* some data memory space maybe allocated dynamiclly, so you must release them when clear or delete them from container. 
* when set hash table, the key must not exist, if it exist, you must delete it manually. this design is because value_point maybe allocated dynamically, so we shouldn't cover it directlly.
* container save all data as void point, so you must transfer it back manually when you want use it.
