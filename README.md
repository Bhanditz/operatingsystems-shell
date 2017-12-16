# CS350 Create Your Own Shell

## Description

This assignment helps you learn about processes and basic process management in a shell. You are asked to write a simple shell program called minish. This shell must work as follows. You start the shell by running minish program. This will give a prompt of your shell as follows:

minish> <br />
From here onwards, you should be able to execute and control any program/command just as you would in a normal shell. For instance<br />
minish> ls <br />
[ Output of ls shown here. Your shell waits for ls to finish. ]<br />
minish> <br />
<br />
Additionally, your shell should be able to do the following:<br />
<br />
Execute commands with multiple arguments. For example:<br />
		minish> Command arg1 arg2 arg3 <br />
		[ Output of Command shown here. Your shell waits for Command to finish. ] <br />
		minish> <br />
		<br />
Execute commands in either foreground or background mode. In foreground mode, the shell just waits for the command to complete before displaying the shell prompt again (as in the above example). In background mode, a command is executed with an ampersand & suffix. The shell prompt appears immediately after typing a command name (say Command1) and shell becomes ready to accept and execute the next command (say Command2), even as Command1 continues executing in the background. For example: <br /> <br />
		minish> Command1 & <br />
		minish> Command2 <br />
		[Output of Command1 and Command2 may interleave here in arbitrary order. Your shell waits for Command 2 to finish.] <br />
		minish> <br />
Maintain multiple processes running in background mode simultaneously. For example: <br />
		minish> Command1 & <br />
		minish> Command2 & <br />
		minish> Command3 & <br />
		minish> <br />
		[Output of Command1, Command2, and Command3 may interleave here in arbitrary order. Shell does not wait for any of the commands to finish.] <br />

		<br />
List all currently running background jobs using "listjobs" command.<br />
		minish> Command1 & <br />
		minish> Command2 & <br />
		minish> Command3 & <br />
		minish> listjobs <br />
		List of backgrounded processes:  <br />
		Command 1 with PID 1000 Status:RUNNING  <br />
		Command 2 with PID 1005 Status:RUNNING  <br />
		Command 3 with PID 1007 Status:FINISHED  <br />
		minish>  <br />
		 <br />
Bring a background process to foreground using the fg command with process ID as argument. For instance, continuing from the previous example:  <br />
		minish> fg 1005  <br />
		[ Your shell waits for Command2 to finish. ]  <br />
		minish>  <br />
		 <br />
Terminate a process by pressing [Ctrl-C]. Your shell must not get killed; only the process running inside your shell must terminate.  <br />
The exit command should terminate your shell. Take care to avoid orphan processes. <br />
The cd command must actually change the directory of your shell and the pwd command must return the current directory of your shell. Note that normal fork-exec mechanism won't work here. Why?  <br />

### Do Nots:
 <br />
DO NOT use any special wrapper libraries or classes to borrow the basic functionality required in this assignment. If in doubt, ask the instructor first BEFORE doing so.  <br />
DO NOT use the system(...) syscall to execute the programs in your shell directly.  <br />
DO NOT write five or six different programs, one for each feature. Write one single program that includes all the above features.
 <br />
### Hints:
 <br />
Build and test one functionality at a time.
Make backup copies of partially working versions of your code. This way, if you irreparably screw up your code, then you can at least roll back to your last backup copy.
First design your data structures and code-structure before you begin coding each feature. Anticipate specific problems you will face.  <br />
 <br />
Check out man page for the following:  <br />
fork()  <br />
execv(), execl(), execlp(), execvp() (which one should you use?)  <br />
waitpid()  <br />
kill() <br />
chdir()  <br />
getcwd()  <br />
 <br />
## Grading Guidelines

This is how we will grade your assignment during the demo. So please prioritize your work accordingly.
 <br />
The final score = part1 + part2.
 <br />
### Part1 Program Demo

5 - README, Makefile, Compilation without errors  <br />
10 - Executing a command with no arguments in foreground  <br />
10 - Executing a command with multiple arguments in foreground  <br />
10 - Executing a single command in background  <br />
10 - Executing multiple commands in background simultaneously  <br />
10 - Printing an accurate list of background processes with listjobs command.  <br />
15 - Bringing a background process to foreground using the fg command.  <br />
10 - Terminating a foreground process using Ctrl+C without killing the shell, and killing minish using exit.  <br />
10 - Implementation of cd and pwd command  <br />
10 - Error Handling: Most important part here is to make sure that you check and handle the errors returned by ALL systems calls used in your program. Also check for other common error conditions in your program. But don't go overboard with error checking. We will not try to intentionally break your code with bad input that may be irrelevant to the assignment's goals.
 <br />
Total score of part1 = 100

### Part2 Answering Questions

TAs will ask the questions about this project/your code. You need to fully understand this project and your implementation.  <br />
Total score of part2 = 100
