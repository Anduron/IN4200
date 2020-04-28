CC := gcc

CFLAGS = -std=c11

PROFILE := -pg

DEP = $(wildcard src/*.h)
OBJ = $(wildcard src/*.c)

.PHONY : all clean

main_serial.x : main_serial.c $(DEP)
	$(CC) $< -o $@ $(OBJ) $(CFLAGS)

#mpi_main.x : mpi_main.c $(DEP)
#	$(CC) $< -mpicc -o $@ $(OBJ) $(CFLAGS)


clean :
	rm -f *.o *.x

print-%  : ; @echo $* = $($*)
