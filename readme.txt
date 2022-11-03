GENERAL NOTES
-Use 'make norm' to norminette only the included files of the project exluding libft
-We should probably print the current directory in the prompt like bash.
-single and double quotes don't work quite like bash, works for now but needs further refinement
-Running executables is a bit janky for some reason
-Commands should only be added to the history if it is valid
-command cd does not work because it is a child process now. dunno how to fix
-command cd should go to base directory if no arguments
-need to account for standard error, is all standard out rn
-redirections to file make a new file if it dont exist
-redirection > doesnt ovrwrite properly

EVAL DOC:
	Compile ✅

	Simple Command & global variables ❌ 
		- Too many global variables (just remove debug when we're done, easy fix)
		- Inputting only spaces does not skip line
		- Cannot input tab, readline interprets as searching for a file. might be ok. 

	Arguments & history ✅

	echo ❌
		- echo with '-n' option prints an erronious space before the output

	exit ❌
		-Exit prints a command not found error but otherwise works

	Return value of a process ❌
		- needs a closer look

	Signals ✅

	Double Quotes ✅

	Single Quotes ✅

	env ❌
		- seg faulting

	export ❌
		- cant test cause of env seg faulting

	unset ❌
		- cant test cause of env seg faulting
	
	cd ✅

	pwd ✅

	Relative Path ✅

	Environment path ❌
		- needs execve to test

	Redirection ❌
		- ">" does not reset file

	Pipes ❌
		- need to execve "grep"

	Go Crazy and history ❌
		- need to execve "ls"

	Environment variables ❌
		- need to handle double quotes

TASKS TO BE COMPLETED
jaymie
-Double quote handling (comment in get_options.c) (echo "$USER") does not work


-builtin 'export', no options
-builtin 'unset', no options
-builtin 'env', no options or arguments
-Environment variables (testing)


ben
-add executable command check instead of immediate "command not found"
-stderr with pipes


-Handle ctrl-C, ctrl-D and ctrl-\ while executing
-Handle ctrl-C, ctrl-D and ctrl-\ while in interactive mode


-We might need to do "ls" at some point maybe????? its in the eval doc on discord


BONUS TASKS TO BE COMPLETED (?)
-'&&', '||' and parenthesis for priorities
-Wildcards (*) for the working directory


TASKS COMPLETED (?):
-Basic main loop
-Display prompt when waiting
-History for input (bsemmler)
-Launching executables
-Single quote handling
-Pipes ('|' character)
-builtin 'echo', option '-n'
-Redirection '<' for redirecting input
-Redirection '<<' should be given a delimiter to read input until it is seen. Doesnt
	update history.
-Handle '\';
-Redirection '>' for redirecting output
-builtin 'cd' with only relative and absolute paths
-builtin 'pwd', no options

STUFF TO TEST:
-Test edge cases with the '\' character, like quotations.
-Need to go through eval document to make sure everything works as needed

KNOWN BUGS:
-echo with '-n' option adds a space before the output string
-Return value doesnt work with pipes

|| is the OR operator. It executes the command on the right only if the command on the left returned an error
&& The second command will only execute if the first command has executed successfully

TO ADD PREEXISTING EXECUTABLES FOR COMMANDS
check for executable in the path directory (check each folder). when found, run the command using execve.
