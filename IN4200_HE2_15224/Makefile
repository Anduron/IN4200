CC := gcc

ifeq ($(shell uname -n), Antares)
	MPICC := mpicc
else
	MPICC := /usr/lib64/openmpi/bin/mpicc
endif

CFLAGS = -O3 -std=c11

PROFILE := -pg

DEP_SERIAL = src/helper_func.h src/count_friends_of_ten.h
OBJ_SERIAL = src/count_friends_of_ten.c

DEP_MPI = src/helper_func.h src/mpi_count_friends_of_ten.h
OBJ_MPI = src/mpi_count_friends_of_ten.c

.PHONY : all clean

main_serial.x : main_serial.c $(DEP_SERIAL)
	$(CC) $< -o $@ $(OBJ_SERIAL) $(CFLAGS)

mpi_main.x : mpi_main.c $(DEP_MPI)
	$(MPICC) $< -o $@ $(OBJ_MPI) $(CFLAGS)

benchmark.x : mpi_main.c $(DEP_SERIAL) $(DEP_MPI)
	$(MPICC) $< -o $@ $(OBJ_SERIAL) $(OBJ_MPI) $(CFLAGS)

clean :
	rm -f *.o *.x

print-%  : ; @echo $* = $($*)
