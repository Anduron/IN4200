CC := gcc

CFLAGS = -std=c99

PROFILE := -pg

#DEP = src/helper_func.h src/read_graph_from_file1.h src/read_graph_from_file2.h src/count_mutual_links1.h src/count_mutual_links2.h src/top_n_webpages.h
#OBJ = src/read_graph_from_file1.c src/read_graph_from_file2.c src/count_mutual_links1.c src/count_mutual_links2.c src/top_n_webpages.c

DEP = $(wildcard src/*.h)
OBJ = $(wildcard src/*.c)

.PHONY : all clean

main.x : main.c $(DEP)
	$(CC) $< -o $@ $(OBJ) $(CFLAGS)

mainOMP.x : main.c $(DEP)
	$(CC) $< -fopenmp -o $@ $(OBJ) $(CFLAGS)

test.x : test.c $(DEP)
	$(CC) $< -o $@ $(OBJ) $(CFLAGS)

testOMP.x : test.c $(DEP)
	$(CC) $< -fopenmp -o $@ $(OBJ) $(CFLAGS)

benchmark.x : benchmark.c $(DEP)
	$(CC) $< -o $@ $(OBJ) $(CFLAGS)

benchmarkOMP.x : benchmark.c $(DEP)
	$(CC) $< -fopenmp -o $@ $(OBJ) $(CFLAGS)


clean :
	rm -f *.o *.x

print-%  : ; @echo $* = $($*)
