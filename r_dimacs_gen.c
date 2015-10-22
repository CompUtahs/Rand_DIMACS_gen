// generates random dimacs file via arguments for number of terms and clauses(respectivly).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	// file descriptor
	int fd;
	// the file to be written
	FILE* f;

	int n_terms = 0;
	int n_clauses = 0;

	// sanity checks
	//	check for correct number of args
	if(argc != 3)
	{
		printf("Please enter exactly 2 arguments!\n");
		return 0;
	}
	//	check for correct format of args, non positive values are not acceptable in either case.
	if((n_terms = atoi(argv[1]) < 1) || (n_clauses = atoi(argv[2]) < 1))
	{
		printf("Invalid args!!\n");
		return 0;
	}// <-- end of sanity checks

	f = fopen("random_dimacs.txt", "w");

	// write the header...
	fwrite("c\n", 1, 2, f);
	fwrite("c\n", 1, 2, f);  // TODO: maybe have an explanatino of user supplied args...???..??
	fwrite("c\n", 1, 2, f);
	fwrite("c\n", 1, 2, f);
	fwrite("p cnf ", 1, 6, f);
	fwrite(argv[1], 1, strlen(argv[1]), f);
	fwrite(" ", 1, 1, f);
	fwrite(argv[2], 1, strlen(argv[2]), f);
	fwrite("\n", 1, 1, f);




	return 0;
}