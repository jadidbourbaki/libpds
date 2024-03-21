CC=gcc
CFLAGS=-Wall -Werror
DEPS=
ODIR=obj
BINDIR=bin

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hash_test: $(ODIR)/hash_test.o $(ODIR)/hash.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

bloom_test: $(ODIR)/bloom_test.o $(ODIR)/bloom.o $(ODIR)/hash.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

.PHONY: test

test: hash_test bloom_test
	./bin/hash_test
	./bin/bloom_test

.PHONY: clean clean_odir clean_bindir

clean_odir:
	rm -rf $(ODIR) && mkdir -p $(ODIR)

clean_bindir:
	rm -rf $(BINDIR) && mkdir -p $(BINDIR)

clean: clean_odir clean_bindir
