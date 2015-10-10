#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_trie.h"

entry *findName(char lastname[], entry *e)
{
    e = e->pChild;
    if(lastname[0] == '\0') return e;
    while (e != NULL) {
        while(e->pNext != NULL && e->ch != lastname[0])
            e = e->pNext;
        if(e->ch == lastname[0]) return findName(lastname+1, e);
        return NULL;
    }
    return NULL;
}

entry *append(char lastname[], entry *e)
{
    if(e->pChild != NULL) {
        e = e->pChild;
        while(e->ch != lastname[0] && e->pNext != NULL)
            e = e->pNext;
        if(e->ch == lastname[0]) append(lastname+1, e);
        else {
            e->pNext = (entry *) malloc(sizeof(entry));
            e = e->pNext;
            e->ch = lastname[0];
            e->pNext = e->pChild = NULL;
            if(lastname[0]!='\0') append(lastname+1, e);
        }
    } else {
        e->pChild = (entry *) malloc(sizeof(entry));
        e = e->pChild;
        e->ch = lastname[0];
        e->pChild = e->pNext = NULL;
        if(lastname[0]!='\0') append(lastname+1, e);
    }
    return NULL;
}

