#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_trie.h"

entry *findName(char lastname[], entry *e)
{
    int i, alphNum, n = strlen(lastname);
    for(i=0; i<=n; ++i) {
        if(lastname[i]>='a') alphNum = lastname[i]-'a';
        else if(lastname[i]>='A') alphNum = lastname[i]-'A';
        else alphNum=26; // '\0'
        e = e->pChild[alphNum];
        if(e == NULL) return NULL;
    }
    return e;
}

entry *append(char lastname[], entry *e)
{
    entry *pHead = e;
    int i, j, alphNum, n = strlen(lastname);
    for(i=0; i<=n; ++i) {
        if(lastname[i]>='a') alphNum = lastname[i]-'a';
        else if(lastname[i]>='A') alphNum = lastname[i]-'A';
        else alphNum=26; // '\0'
        if(e->pChild[alphNum] != NULL)
            e = e->pChild[alphNum];
        else {
            e->pChild[alphNum] = (entry *) malloc(sizeof(entry));
            e = e->pChild[alphNum];
            for(j=0; j<27; ++j) e->pChild[j] = NULL;
            e->ch = lastname[i];
        }
    }
    return pHead;
}

void releaseList(entry **pHead)
{
    if( (*pHead) != NULL) {
        int i;
        for(i=0; i<27; ++i)
            if( (*pHead)->pChild[i] != NULL)
                releaseList(&(*pHead)->pChild[i]);
        free(*pHead);
    }
}

