# CISC 324 Lab 1

Completed by: Dallas Doherty\
Student Number: 20220683

# 1 Process Communication Issue

**Question 1** \
The final if statement, PID != 0 only takes into account the parent process. 
PID is equal to fork; it creates two instances from that point on in the program. 
One instance of the PID is going to be a parent and the other the child, they both run at the same time. 
At the end of the function the final if statement is only valid for the parent process, only the parent process is 
getting printed. Currently the parent process has no way of acquiring the information from the child process.

**Question 2** \
First I initialized the variable status up at the top of the main function. Then I added wait(&status) [The address of status]
This ensures that the child process completes before the parent process is computed. In order for the child process total to
be added to the grand total I added an exit with the parameters of total encompassed in the child process else statement.
Now this will trigger the if(WIFEXITED(status)) and the total of the child process will be taken into consideration of the 
complete total. Not just the total of the parent process will be printed.

**Question 3**\
The value of n is 26. This is because the max value that the POSIX can account for is 255. When n is 26 one of the halves of
computation is greater than 255 therefore it sends an inaccurate value.

**Question 4**\
When you switch the parent and child process the value of n increases to 46. For the same reason as above, however since 
the child process now has the lower values and does the first half of computation the program can account for a greater value.

# 2 Race-Condition Issue

**Question 1**\
Since two child processes are running at the same instance and executing the same piece of code with the output dependent on 
the order of execution they are overwriting each other.

**Question 2**\
5000, if all the child processes fail, the parent process will still execute therefore the lowest possible n is 5000.