CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99
GOAL = ./phonebook_orig

EXEC = phonebook_orig phonebook_bst phonebook_trie phonebook_opt
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_bst: $(SRCS_common) phonebook_bst.c phonebook_bst.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -DBST -o $@ \
		$(SRCS_common) $@.c

phonebook_trie: $(SRCS_common) phonebook_trie.c phonebook_trie.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -DTRIE -o $@ \
		$(SRCS_common) $@.c

run: $(EXEC)
	watch -d -t ./phonebook_orig

perf:
	echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh
	perf stat -r 10 -e cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses,L1-icache-load-misses $(GOAL)

clean:
	$(RM) $(EXEC) *.o perf.*
