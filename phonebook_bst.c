#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_bst.h"

bst *findName(char lastname[], bst *root)
{
    while (root != NULL) {
        int res = strcasecmp(lastname, root->lastName);
        if(res == 0) return root;
        return findName(lastname, res < 0 ? root->pL : root->pR);
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

bst *convert_to_bst(entry **pHead, int n)
{
    bst *pL, *root;
    if(n<=0) return NULL;
    /* get left leaf */
    pL = convert_to_bst(pHead, n>>1);
    /* build root */
    root = (bst *) malloc(sizeof(bst));
    strcpy(root->lastName, (*pHead)->lastName);
    root->pL = pL;
    /* get right leaf & free link-list*/
    entry *tmp = *pHead;
    *pHead = (*pHead)->pNext;
    free(tmp);
    root->pR = convert_to_bst(pHead, n-(n>>1)-1);
    return root;
}

