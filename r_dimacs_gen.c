// generates random dimacs file via arguments for number of terms and clauses(respectivly).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// randomly returns one or zero(positive or negative)
int pos_neg();
// randomly returns the number of terms for a clause
int n_clause_terms(int n_terms);
// randomly returns a number within the range of terms
int r_term(int n_terms);          					// TODO: might be needlessly redundant.....

// detects duplicate terms
int contains(int* terms, int term, int terms_per_clause);

//make a clause
void make_clause(int* clause, int terms_per_clause);

// holds the current clause' terms
int* terms;

int main(int argc, char* argv[])
{
	// file descriptor
	int fd;
	// the file to be written
	FILE* f;
	// number of terms per clause
	int terms_per_clause;

	int n_terms = 0;
	int n_clauses = 0;

	int clause_pos = 0; // indexer
	char* parsed_term; // integer parsed to a string

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
	fwrite("c\n", 1, 2, f);  // TODO: comments...???..??
	fwrite("c\n", 1, 2, f);
	fwrite("c\n", 1, 2, f);
	fwrite("p cnf ", 1, 6, f);
	fwrite(argv[1], 1, strlen(argv[1]), f);  // terms
	fwrite(" ", 1, 1, f);
	fwrite(argv[2], 1, strlen(argv[2]), f);  // clauses
	fwrite("\n", 1, 1, f);

	n_terms = atoi(argv[1]);
	n_clauses = atoi(argv[2]);
	//printf("n_clauses: %d\n", n_clauses);

	while(n_clauses > 0)
	{
		// get how many terms the current clause will contain
		terms_per_clause = n_clause_terms(n_terms);

		// allocate terms array
		terms = calloc(terms_per_clause, sizeof(int));

		// fill the clause array
		make_clause(terms, terms_per_clause);  // <-- function is suspect...

		// reset
		clause_pos = 0; 
		parsed_term = "";


		// write the clause
		while(clause_pos < terms_per_clause)
		{
			printf("bus error?\n");
			printf("terms[clause_pos]: %d", terms[clause_pos]);

			// parse the current term to a string
		 	sprintf(parsed_term, "%d", terms[clause_pos]); // <-- SEG FAULT!!

			

			// if positive
			if(pos_neg() == 1)
			{
				// write term
				fwrite(parsed_term, 1, strlen(parsed_term), f);
				// write space
				fwrite(" ", 1, 1, f);
			}
			// else if negative
			else
			{
				// write negative
				fwrite("-", 1, 1, f);
				// write term
				fwrite(parsed_term, 1, strlen(parsed_term), f);
				// write space
				fwrite(" ", 1, 1, f);
			}

			clause_pos++;
		}

		fwrite("0\n", 1, 2, f);

		free(terms);
		n_clauses--;
	}

	return 0;
}

// 0 for negative, 1 for positive
int pos_neg()
{
	return (rand() % 2);
}

// return randomly generated 1 - n_terms number.
int n_clause_terms(int n_terms)
{
	return ((rand() % n_terms) + 1); // <-- no zeroes!, can't have zero terms per clause or zero clauses
}

void make_clause(int* terms, int terms_per_clause)
{
	int pos = 0;
	int term = 0;

	while(pos < terms_per_clause) // suspect
	{
		// get a random number
		term = n_clause_terms(terms_per_clause);

		// if the terms array already contains the randomly generated term.
		if(contains(terms, term, terms_per_clause) == 1)
		{
			continue;
		}
		// else put it in the array
		else
		{
			assert(term > 0);
			terms[pos] = term;

			printf("terms[pos]: %d\n", terms[pos]);

			pos++;
		}
	}
}

int contains(int* terms, int term, int terms_per_clause)
{
	int pos = 0;

	while(pos < terms_per_clause)
	{
		if(terms[pos] == term)
		{
			return 1;
		}
		pos++;
	}

	return 0;
}
