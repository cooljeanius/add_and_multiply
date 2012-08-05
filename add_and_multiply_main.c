/*
 * Eric Gallager
 *
 */

#include "libgetnumber.h" // contains GetNumber() function

/* 
 * Adder: Adds two numbers together and prints the result. Doesn't return anything.
 */
void adder(int input1[], int input2[], int output[]); // Prototype
void adder(int input1[], int input2[], int output[]) {
	int j = 0; // declare loop-counter
	for (j = 0; j < LENGTH; j++) // Go through entire output array
	{
		output[j] = (input1[j] + input2[j] + output[j]); // Add arrays together (Adding it to itself is just in case there's already something into it due to place value)
		if (output[j] >= 10) { // handle place-value
			output[j] = output[j] - 10; // You only ever carry a 1 when adding 2 numbers
			output[j+1]++; // Put into next digit
		}
	}
	j--; // Put j back down to the array size
	while (output[j] == 0) // Skip past all the 0s (with j-- below)
	{
		j--;
	}
	while (j >= 0) // Go through array backwards to print it (with j-- below)
	{
		printf("%i", output[j]);
		j--;
	}
	printf(" \n "); // I like putting extra whitespace in
}	

/* 
 * Multiplier: Multiplies two numbers together and prints the result. Doesn't return anything.
 */
void multiplier(int input1[], int input2[], int output[], int arglen1, int arglen2); // Prototype
void multiplier(int input1[], int input2[], int output[], int arglen1, int arglen2) {
	int j = 0; // declare loop-counter (for the first factor)
	int k = 0; // we're going to need a second loop-counter because it's multiplication (k is for the second factor)
	int temp = 0; // for carrying
	// malloc(100000); // this takes some extra processing power, unfortunately I don't know how to use malloc properly, so this will stay commented out for now
	// output[j] = 0; // clear out
	for (k = 0; k < (LENGTH - 1); k++) { // need a separate loop because in multiplication, each digit is multiplied by each other, not just the one in the same place like in addition
		for (j = 0; j < (LENGTH - 1); j++) // Go through entire output array
		{
			// printf("\n (j + k) (i.e. %i + %i) = %i \n", j, k, (j+k)); // Statement for debugging
			// printf("\n output[j+k] (i.e. output[%i]) = %i (this digit gets carried) \n", (j+k), output[j+k]); // Statement for debugging
			temp = output[j+k]; // storing place value in a temp variable so it doesn't interfere 
			// printf("\n temp = %i \n", temp); // Statement for debugging			
			output[j+k] = (input1[j] * input2[k]); // Multiply arrays together 
			// printf("\n input1[%i] * input2[%i] = %i (this is what output[j+k] becomes) \n", j, k, output[j+k]); // Statement for debugging
			output[j+k] = (temp + output[j+k]); // Adding it to itself is just in case there's already something into it due to place value (splitting it off as a second step for finer-grained debugging)
			// printf("\n output[j+k] (i.e. output[%i]) = %i (this is adding the carried digit which was held in temp) \n", (j+k), output[j+k]); // Statement for debugging
			while (output[j+k] >= 10) { // handle place-value (changed to a while-loop because multiplication can carry more than just 1)
				// printf("\n j = %i	", j); // Statement for debugging
				output[j+k] = (output[j+k] - 10); // Subtract 10 at a time, if there's still more than 10, get it the next time the loop goes around
				// printf("		output[j+k] (i.e. output[%i]) = %i   		", (j+k), output[j+k]); // Statement for debugging
				output[(j+k)+1]++; // Put into next digit
				// printf("	output[(j+k)+1] (i.e. output[%i]) = %i ", ((j+k)+1), output[(j+k)+1]); // Statement for debugging
			}
			// printf("\n"); // extra whitespace
			// printf("\n output[j] (i.e. output[%i]) = %i \n", j, output[j]); // Statement for debugging
			// printf("\n output[j+k] (i.e. output[%i]) = %i (this digit gets held) \n", (j+k), output[j+k]); // Statement for debugging
		}
		// printf("\n k = %i \n", k); // Statement for debugging
	}
	j--; // Put j back down to the array size
	while (output[j] == 0) // Skip past all the 0s (with j-- below)
	{
		j--;
	}
	while (j >= 0) // Go through array backwards to print it (with j-- below)
	{
		printf("%i", output[j]);
		j--;
	}
	printf(" \n "); // I like putting extra whitespace in
}	

/*
 * Main: The main function
 */
int main (int argc, const char * argv[]) { // Convention for declaring main() from the C specification
    int which_operation = 0; // for telling adding and multiplying apart
	int flag = 0; // truth flag
	char* string_to_print[8]; // Declare but don't initialize yet, I want to initialize it conditionally
	while (flag == 0) { // do this until the input is valid
		printf("\n Enter 1 to add, or 2 to multiply> "); // prompt
		scanf("%d", &which_operation); // get input
		// printf("\n which_operation = %d \n", which_operation); // Statement for debugging
		if (which_operation == 1) {
			*string_to_print = "add"; // choice will be used later on, store to variable
			printf("\n You are %sing. \n", *string_to_print);
			flag++; // get out of loop
		} else if (which_operation == 2) {
			*string_to_print = "multiply"; // choice will be used later on, store to variable
			printf("\n You are %sing. \n", *string_to_print);
			flag++; // get out of loop
		} else {
			printf("\n Invalid option specified. Please try again. \n");
		}
	}
	if (argc != 3) { // check to make sure number of arguments is correct
		printf("\n Incorrect number of arguments specified! This program can only %s 2 numbers. \n", *string_to_print); // just in case
		printf(" Please try again. \n");
		exit(0); // end program, with 0 because even though this is a failure, it isn't an error though.
	} else {
		printf("\n You are %sing _%i_ numbers. \n", *string_to_print, argc-1);
	}
	int MyFirstNumber[LENGTH]; // Output array
	int j = 0; // Initialize loop-counter
	for (j = 0; j < LENGTH; j++) // goes through each element of MyFirstNumber[]
	{
		MyFirstNumber[j] = 0; // sets each array element in MyFirstNumber[] to 0
	}
    int arglen1 = GetNumber((char*)argv[1], (int*)MyFirstNumber); // Get number from string, and length of number as well
	int MySecondNumber[LENGTH]; // output array for second number
	for (j = 0; j < LENGTH; j++) // goes through each element of MySecondNumber[]
	{
		MySecondNumber[j] = 0; // sets each array element in MySecondNumber[] to 0
	}
	int arglen2 = GetNumber((char*)argv[2], (int*)MySecondNumber); // Repeat what we just did with the first number with our second
	int Answer[LENGTH];
	for (j = 0; j < LENGTH; j++) // goes through each element of Answer[]
	{
		Answer[j] = 0; // sets each array element in Answer[] to 0
	}
	if (which_operation == 1) { // if adding,
		printf("\n %s + %s = ", argv[1], argv[2]);
		adder(MyFirstNumber, MySecondNumber, Answer); // do adding function
	} else if (which_operation == 2) { // if multiplying,
		printf("\n %s x %s = ", argv[1], argv[2]);
		multiplier(MyFirstNumber, MySecondNumber, Answer, arglen1, arglen2); // do multiplication function
		// printf("\n (multiplication doesn't work yet) \n"); // placeholder
	} else {
		printf("\n This shouldn't happen. Something must have gone wrong. \n"); // just in case
	}
	
    return 0;
}

// newline \n

