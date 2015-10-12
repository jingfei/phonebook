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

typedef struct __PHONE_BOOK_TRIE {
    char ch;
    entry_detail *detail;
    struct __PHONE_BOOK_TRIE *pChild[27];
} entry;

entry *findName(char lastname[], entry *t);
entry *append(char lastName[], entry *e);
entry *getNode();
void releaseList(entry **pHead);

#endif

