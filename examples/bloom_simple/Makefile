bloom_simple: bin_dir bloom_simple.c
	gcc -I ../../src bloom_simple.c -L ../../bin -lprobability -o bin/bloom_simple

.PHONY: bin_dir clean

bin_dir:
	mkdir -p bin/

clean: 
	rm -rf bin/
