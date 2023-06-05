.phony all:
all: SCA_Safe_RSA

SCA_Safe_RSA: generatePrime.c
	gcc generatePrime.c -o gp

.PHONY clean:
clean:
	-rm -rf *.o *.exe