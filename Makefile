CC=gcc
CFLAGS=
DEPS=
ODIR=obj
BINDIR=bin

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fnv1a_test: $(ODIR)/fnv1a_test.o $(ODIR)/fnv1a.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

.PHONE: clean clean_odir clean_bindir

clean_odir:
	rm -rf $(ODIR) && mkdir -p $(ODIR)

clean_bindir:
	rm -rf $(BINDIR) && mkdir -p $(BINDIR)

clean: clean_odir clean_bindir


