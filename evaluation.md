
# Minishell Evaluation

## Mandatory Part

### Compile

- [x] Use `make -n` to see if compilation use `-Wall -Wextra -Werror`. If not, select the "invalid compilation" flag.
- [x] minishell compiles without any errors. If not, select the flag.
- [x] The Makefile must not re-link. If not, select the flag.

### Simple Command & global variables

If something crashes, select the "crash" flag. If something doesn't work, select the "incomplete work" flag.

- [x] Execute a simple command with an absolute path like `/bin/ls`, or any other command without any options.
- [x] How many global variables are used? Why? Ask the evaluated student to give you a concrete example of why it feels mandatory or logical.
- [x] Check the global variable. This global variable cannot provide any other information or data access than the number of a received signal.
- [x] Test an empty command.
- [x] Test only spaces or tabs.

### Arguments

If something crashes, select the "crash" flag. If something doesn't work, select the "incomplete work" flag.

- [x] Execute a simple command with an absolute path like `/bin/ls`, or any other command with arguments but without any quotes or double quotes.
- [x] Repeat multiple times with different commands and arguments.

### echo

If something crashes, select the "crash" flag. If something doesn't work, select the "incomplete work" flag.

- [x] Execute the `echo` command with or without arguments, or the `-n` option.
- [x] Repeat multiple times with different arguments.

### exit

If something crashes, select the "crash" flag. If something doesn't work, select the "incomplete work" flag.

- [x] Execute `exit` command with or without arguments.
- [x] Repeat multiple times with different arguments.
- [x] Don't forget to relaunch the minishell

### Return value of a process

If something crashes, select the "crash" flag. If something doesn't work, select the "incomplete work" flag.

- [x] Execute a simple command with an absolute path like `/bin/ls`, or any other command with arguments but without any quotes and double quotes. Then execute `echo $?`
- [x] Check the printed value. You can do the same in bash in order to compare the results.
- [x] Repeat multiple times with different commands and arguments. Try some wrong commands like `/bin/ls filethatdoesntexist`
- [x] Try anything like `expr $? + $?`

### Signals

If something crashes, select the "crash" flag. If something doesn't work, select the "incomplete work" flag.

- [x] `Ctrl`+`C` in an empty prompt should display a new line with a new prompt.
- [x] `Ctrl`+`\` in an empty prompt should not do anything.
- [x] `Ctrl`+`D` in an empty prompt should quit minishell --> RELAUNCH!
- [x] `Ctrl`+`C` in a prompt after you wrote some stuff should display a new line with a new prompt.
- [x] The buffer should be clean too. Press "Enter" to make sure nothing from the previous line is executed.
- [x] `Ctrl`+`D` in a prompt after you wrote some stuff should not do anything.
- [x] `Ctrl`+`\` in a prompt after you wrote some stuff should not do anything.
- [x] Try `Ctrl`+`C` after running a blocking command like `cat` without arguments or `grep "something"`.
- [x] Try `Ctrl`+`\` after running a blocking command like `cat` without arguments or `grep "something"`.
- [x] Try `Ctrl`+`D` after running a blocking command like `cat` without arguments or `grep "something"`.
- [ ] Repeat multiple times using different commands.

### Double Quotes

If something crashes, select the "crash" flag. If something doesn't work, select the "incomplete work" flag.

- [x] Execute a simple command with arguments and, this time, use also double quotes (you should try to include whitespaces too).
- [x] Try a command like: `echo "cat lol.c | cat > lol.c"`
- [x] Try anything except `$`.

### Single Quotes

- [x] Execute commands with single quotes as arguments.
- [x] Try empty arguments.
- [x] Try environment variables, whitespaces, pipes, redirection in the single quotes.
- [x] `echo '$USER'` must print `$USER`.
- [x] Nothing should be interpreted.

### env

- [x] Check if `env` shows you the current environment variables.

### export

- [x] Export environment variables, create new ones and replace old ones.
- [x] Check the result with `env`.

### unset

- [x] Export environment variables, create new ones and replace old ones.
- [x] Use `unset` to remove some of them.
- [x] Check the result with `env`.

### cd

- [x] Use the command `cd` to move the working directory and check if you are in the right directory with `/bin/ls`
- [ ] Repeat multiple times with working and not working `cd`
- [x] Also, try `.` and `..` as arguments.

### pwd

- [x] Use the command `pwd`.
- [x] Repeat multiple times in different directories.

### Relative Path

- [x] Execute commands but this time use a relative path.
- [x] Repeat multiple times in different directories with a complex relative path (lots of `..`).

### Environment path

- [x] Execute commands but this time without any path (`ls`, `wc`, `awk` and so forth).
- [x] Unset the `$PATH` and ensure commands are not working anymore.
- [x] Set the `$PATH` to a multiple directory value (`directory1:directory2`) and ensure that directories are checked in order from left to right.

### Redirection

- [x] Execute commands with redirections `<` and/or `>`
- [ ] Repeat multiple times with different commands and arguments and sometimes change `>` with `>>`
- [x] Check if multiple tries of the same redirections fail.
- [x] Test `<<` redirection (it doesn't have to update the history).

### Pipes

- [x] Execute commands with pipes like `cat file | grep bla | more`
- [ ] Repeat multiple times with different commands and arguments.
- [x] Try some wrong commands like `ls filethatdoesntexist | grep bla | more`
- [x] Try to mix pipes and redirections.

### Go Crazy and history

- [x] Type a command line, then use `Ctrl`+`C` and press "Enter". The buffer should be clean and there should be nothing left to execute.
- [x] Can we navigate through history using Up and Down? Can we retry some command?
- [x] Execute commands that should not work like `dsbksdgbksdghsd`. Ensure minishell doesn't crash and prints an error.
- [x] `cat | cat | ls` should behave in a "normal way".
- [ ] Try to execute a long command with a ton of arguments.
- [ ] Have fun with that beautiful minishell and enjoy it!

### Environment variables

- [x] Execute `echo` with some environment variables (`$variable`) as arguments.
- [ ] Check that `$` is interpreted as an environment variable.
- [x] Check that double quotes interpolate `$`.
- [x] Check that `USER` exists. Otherwise, set it.
- [x] `echo "$USER"` should print the value of the `USER` variable.

## Bonus

Evaluate the bonus part if, and only if, the mandatory part has been entirely and perfectly done, and the error management handles unexpected or bad usage. In case all the mandatory points were not passed during the defense, bonus points must be totally ignored.

### And, Or

- [ ] Use `&&`, `||` and parenthesis with commands and ensure minishell behaves the same way bash does.

### Wildcard

- [ ] Use wildcards in arguments in the current working directory.

### Surprise! (or not...)

- [x] Set the `USER` environment variable.
- [x] `echo "'$USER'"` should print the value of the `USER` variable.
- [x] `echo '"$USER"'` should print `"$USER"`.
