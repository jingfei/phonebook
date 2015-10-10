#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry_detail;

typedef struct __PHONE_BOOK_SIMPLE {
    union {
        char lastName[MAX_LAST_NAME_SIZE];
        entry_detail *detail;
    };
    struct __PHONE_BOOK_SIMPLE *pNext;
} entry;

typedef struct __PHONE_BOOK_BST {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_BST *pL;
    struct __PHONE_BOOK_BST *pR;
} bst;

bst *findName(char lastname[], bst *root);
entry *append(char lastName[], entry *e);
bst *convert_to_bst(entry **pHead, int n);

#endif
