CC=gcc
CFLAGS=-Wall -Werror
DEPS=
ODIR=obj
BINDIR=bin
NAME=libprobability
SRC=src

lib: $(ODIR)/hash.o $(ODIR)/bloom.o $(ODIR)/pt_bloom.o
	ar rcs $(BINDIR)/$(NAME).a $^

$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hash_test: $(ODIR)/hash_test.o $(ODIR)/hash.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

bloom_test: $(ODIR)/bloom_test.o $(ODIR)/bloom.o $(ODIR)/hash.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

pt_bloom_test: $(ODIR)/pt_bloom_test.o $(ODIR)/pt_bloom.o $(ODIR)/hash.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

.PHONY: test

test: hash_test bloom_test pt_bloom_test
	./bin/hash_test
	./bin/bloom_test
	./bin/pt_bloom_test

.PHONY: clean clean_odir clean_bindir

clean_odir:
	rm -rf $(ODIR) && mkdir -p $(ODIR)

clean_bindir:
	rm -rf $(BINDIR) && mkdir -p $(BINDIR)

clean: clean_odir clean_bindir

