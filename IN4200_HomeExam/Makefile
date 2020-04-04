CC := gcc

CFLAGS = -Wall -std=c11

PROFILE := -pg

DEP = src/helper_func.h src/read_graph_from_file1.h src/count_mutual_links1.h
OBJ = src/read_graph_from_file1.c src/count_mutual_links1.c

.PHONY : all clean

main.x : main.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

test.x : test.c $(DEP)
	$(CC) $< -o $@ $(OBJ)

clean :
	rm -f *.o *.x

print-%  : ; @echo $* = $($*)
