GENERAL NOTES
-Use 'make norm' to norminette only the included files of the project exluding libft
-Current approach to splitting commands and options will not work once we want to 
	implelent pipes as it only works for single commands.
-We should probably print the current directory in the prompt like bash. -b
-Is '&' good for a prompt end? I wanted to differentiate from bash's '$' -b
-Might be a good idea to mark comments with '-b and '-j' -b
-echo doesnt count multiple spaces between words, reads from args
-single and double quotes don't work quite like bash, works for now but needs further refinement
-Running executables is a bit janky for some reason


CODING STANDARD:
I've made some extra coding standard rules to keep our project looking consistent
and help prevent major confusion as we add to the project. If you would like something
changed or removed/would like to add your own/just general questions let me know

-Make sure your code follows the norminette before pushing it to the repos. Comment
	related errors and anything that is only temporary are fine though
-Try to eliminate any leaks as you find them, though we'll do run a test for it when
	we're almost ready to submit
-Main.c should only contain the main function
-If a file is named after a function, then it should only contain that function and
	any functions meant specifically to assist that function
-Generally, a single file should only contain functions meant for a single purpose,
	and the functions should be in decreasing order of scope with any prototypes at 
	the top of the file. Basically, the most important function should the first
	function of the file.


TASKS TO BE COMPLETED
-Single quote handling
-Double quote handling
-Redirection '<' for redirecting input
-Redirection '>' for redirecting output
-Redirection '<<' should be given a delimiter to read input until it is seen. Doesnt
	update history.
-Redirection '>>' for redirecting output in append mode
-Pipes ('|' character)
-Environment variables
-Handle '$?'
-Handle ctrl-C, ctrl-D and ctrl-\ while executing
-Handle ctrl-C, ctrl-D and ctrl-\ while in interactive mode
-builtin 'echo' option -n
-builtin 'export', no options
-builtin 'unset', no options
-builtin 'env', no options or arguments


BONUS TASKS TO BE COMPLETED (?)
-'&&', '||' and parenthesis for priorities
-Wildcards (*) for the working directory


TASKS COMPLETED:
-Basic main loop (bsemmler)
-Display prompt when waiting (bsemmler)
-History for input (bsemmler)
-Launching executables (bsemmler)
-builtin 'echo', no options (bsemmler)
-builtin 'cd' with only relative and absolute paths (bsemmler)
-builtin 'pwd', no options (bsemmler)
-builtin 'exit', no options (bsemmler)


KNOWN BUGS:
-No known bugs!