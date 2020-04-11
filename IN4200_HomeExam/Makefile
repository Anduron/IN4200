CC := gcc

CFLAGS = -Wall -std=c11

PROFILE := -pg

#DEP = src/helper_func.h src/read_graph_from_file1.h src/read_graph_from_file2.h src/count_mutual_links1.h src/count_mutual_links2.h src/top_n_webpages.h
#OBJ = src/read_graph_from_file1.c src/read_graph_from_file2.c src/count_mutual_links1.c src/count_mutual_links2.c src/top_n_webpages.c

DEP = $(wildcard src/*.h)
OBJ = $(wildcard src/*.c)

.PHONY : all clean

main.x : main.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

mainOMP.x : main.c $(DEP)
	$(CC) $< -fopenmp -o $@ $(OBJ)

test.x : test.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

testOMP.x : test.c $(DEP)
	$(CC) $< -fopenmp -o $@ $(OBJ)

clean :
	rm -f *.o *.x

print-%  : ; @echo $* = $($*)
