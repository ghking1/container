# container
c container lib, include link list, squence list and hashtable.

### quick start
1. copy .h and .c files to your project
2. include .h file in your source code
4. if you use vs compiler you may need define "_CRT_SECURE_NO_WARNINGS" for the preprocessor
3. use it like fowllowing
```
#include <stdlib.h>
#include <stdio.h>
#include "sqlist.h"

int main(int argc, char **argv)
{
    SqList list;
    SqListNode *node;
    void *temp;
    int  *value;

    init_SqList(&list);

    value  = (int*)malloc(sizeof(int));
    *value = 9;
    pushBack_SqList(&list, value);        //value is a point, all container save point to real data

    node = getFirst_SqList(&list);        
    printf("%d\n", *(int*)(node->data));  //data is void*, so we should transform it to int*

    temp = popBack_SqList(&list);
    free(temp);                           //here we freed temp, so we shouldn't free value again

    destroy_SqList(&list);

    return 0;
}

```

### run test
1. you can use make to run test code in linux
```
cd test
make
./test.exe

```

2. you also can use vs to run test code in windows

double click vs2015_project/container.sln, and run it in vs.

### details
you can take a look at test code, and header files has interface explaination.

### Link List
![image](https://github.com/ghking1/container/raw/master/doc/lklist.png)

### Sequence List
![image](https://github.com/ghking1/container/raw/master/doc/sqlist.png)

### HashTable
![image](https://github.com/ghking1/container/raw/master/doc/hashtable.png)

### something should take attention
* all data are saved as point in container, so the data must not be local variable if you want to use it outly
* some data memory space maybe allocated dynamiclly, so you must release them when clear or delete them from container. 
* when set hash table, the key must not exist, if it exist, you must delete it manually. this design is because data maybe allocated dynamically, so we shouldn't cover it directlly.
* container save all data as void point, so you must transfer it manually when you want use it.
