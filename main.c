#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"
#define INPUT_NUM 8

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0, line_num=0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
#ifdef TRIE
    for(i=0; i<27; ++i) e->pChild[i] = NULL;
#else
    e->pNext = NULL;
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            ++i;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e);
        ++line_num;
    }
#ifdef BST
    /* build the bst */
    bst *root = convert_to_bst(&(pHead->pNext), line_num);
#endif
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);


    /* the givn last name to find */
    char input[INPUT_NUM][MAX_LAST_NAME_SIZE] = {
        "zyxel","uninvolved","whiteshank","odontomous",
        "pungoteague","reweighted","xiphisternal","yakattalo"
    };

#ifdef BST
    for(i=0; i<INPUT_NUM; ++i) {
        assert(findName(input[i],root) &&
               "Did you implement findName() in " IMPL "?");
        assert(0 == strcmp(findName(input[i], root)->lastName, input[i]));
        printf("%s is found\n",input[i]);
    }
#else
    e = pHead;
    for(i=0; i<INPUT_NUM; ++i) {
        assert(findName(input[i], e) &&
               "Did you implement findName() in " IMPL "?");
#ifdef TRIE
        assert(findName(input[i], e)->ch == '\0');
#else
        assert(0 == strcmp(findName(input[i], e)->lastName, input[i]));
#endif
        printf("%s is found\n",input[i]);
    }
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
#ifdef BST
    for(i=0; i<INPUT_NUM; ++i) findName(input[i], root);
#else
    for(i=0; i<INPUT_NUM; ++i) findName(input[i], e);
#endif
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    /* release all allocated entries */
#ifdef BST
    releaseList(&root);
#else
    releaseList(&pHead);
#endif

    return 0;
}
