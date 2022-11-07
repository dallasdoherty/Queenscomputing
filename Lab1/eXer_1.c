/******************************************************************************
Dallas Doherty
20220683
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <math.h>

// A is a function that computes and returns the sum of 0 + 1 + 2 + 3 + ... + k + ... + [y/2]
int A(int y)
{
        int total = 0;
        for(int i=0; i<=floor(y/2);i++) total = total + i;
        return total;
}

// B is a function that computes the sum of [(y/2)+1] + [((y+1)/2)+1] + [((y+2)/2)+1] + ... [((y+k)/2)+1] + ... + y
int B(int y)
{
        int total = 0;
        for(int i=(floor(y/2)+1);i<=y;i++) total = total + i;
        return total;
}

void main (int argc, char *argv[])
{

        int Total =0; //Let Total be the total computed sum to be returned at the end of the program
        pid_t pid;
        int status; //Intilize status


	//The program tests whether the user has input a parameter to the program or not. If not, the program exits.
	//Note that argc contain the number of parameters, whereas argv contains the parameters,
	//Hence, argv[0] contains the first parameter which is the name of the executable file e.g., a.out
	// argv[1] the second, argv[2] the third, and ...

        if(argc==1 || argc>2)
        {
                printf("The program needs one parameter to be executed (e.g., ./a.out 13)\n");
                exit(0);
        }

        //The program grabs the second parameter and converts that into an integer.
	int x = atoi(argv[1]);

	//The program tests whether the input paramter is greater than 0. If not the program exits.
        if (x<=0)
        {
                printf("Unvalid parameter: The parameter should be greater than 0, exiting ... \n");
                exit(0);
        }

        if (x = 1)
        {
            printf("%d",1);
            exit(0);
        }

	//The program (process) create a new child process and a value is return from fork() into pid variable.
        pid = fork();
	    wait(&status); // address of status

	//The program exits if the fork() primitive failes
	if (pid < 0)
	{
		fprintf(stderr, "Fork() system call failed");
		return;
	}

	//If process is the child process then pid==0, else it is the parent (the value contains the PID of the child).
        if (pid != 0)
        {
		//call function A to perform the summation from x to [x/2]
                Total = Total + A(x);
        }
        else
        {
		//call function B to perform the summation from [(x/2)+1] to x.
                Total = Total + B(x);
                exit(Total); //exit status of the total computed.
        }

        if(WIFEXITED(status))
        {
            Total = Total + WEXITSTATUS(status); //total of child process being added to parent process
        }

       //The parent process displays the total and final summation:
       if (pid != 0) // PID for child process is always zero this never runs through
       //only half the total is being displayed.
       //Now that child Total has been added to parent the sum is printed.
       {
                printf("The total is: %d\n",Total) ;
       }

       return;
       //The max value that the POSIX can account for is 255. When n is 26 one of the halves of computation
       // is greater than 255 so it send the wrong number.
       //When you switch the parent and child process then the max value of n is 46. For the same
       //reason above. Since they switched the child process has the lower values and does the first
       //half thus can account for a greater value.
}



