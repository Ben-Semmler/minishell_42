GENERAL NOTES
-Use 'make norm' to norminette only the included files of the project exluding libft
-We should probably print the current directory in the prompt like bash.
-single and double quotes don't work quite like bash, works for now but needs further refinement
-Running executables is a bit janky for some reason
-Commands should only be added to the history if it is valid
-command cd does not work because it is a child process now. dunno how to fix
-command cd should go to base directory if no arguments
-need to account for standard error, is all standard out rn


TASKS TO BE COMPLETED
jaymie
-Double quote handling
-Environment variables
-builtin 'export', no options
-builtin 'unset', no options
-builtin 'env', no options or arguments


ben
-Redirection '<' for redirecting input
-Redirection '>' for redirecting output
-Redirection '<<' should be given a delimiter to read input until it is seen. Doesnt
	update history.
-Redirection '>>' for redirecting output in append mode
-Handle '$?'
-builtin 'exit', no options


-Handle ctrl-C, ctrl-D and ctrl-\ while executing
-Handle ctrl-C, ctrl-D and ctrl-\ while in interactive mode


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
-builtin 'cd' with only relative and absolute paths
-builtin 'pwd', no options


KNOWN BUGS:
-No known bugs! (they are hiding from us)


|| is the OR operator. It executes the command on the right only if the command on the left returned an error
&& The second command will only execute if the first command has executed successfully