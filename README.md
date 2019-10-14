# Simple-Shell
  # Problem Statement:
    It is required to implement a Unix shell program. A shell is simply a program that
    conveniently allows you to run other programs. Read up on your favorite shell to see what it
    does. Your shell must support  the following:
         1. The internal shell command "exit" which terminates the shell
            • Concepts: shell commands, exiting the shell.
            • System calls: exit()
        2. A command with no arguments
            • Example: ls, cp, rm …etc
            • Details: Your shell must block until the command completes and, if the return
            code is abnormal, print out a message to that effect.
            • Concepts: Forking a child process, waiting for it to complete and synchronous
            execution.
            • System calls: fork(), execvp(), exit(), wait()
        3. A command with arguments
            • Example: ls –l
            • Details: Argument 0 is the name of the command.
            • Concepts: Command-line parameters.
        4. A command, with or without arguments, executed in the background using &.
            a. Example: firefox &
            b. Details: In this case, your shell must execute the command and return
              immediately, not blocking until the command finishes.
            c. Concepts: Background execution, signals, signal handlers, processes and
               asynchronous execution.
            d. Requirements: You have to show that the opened process will be nested as a
              child process to the shell program via opening the task manager found in the
              operating system like in Figure 1. Additionally you have to write in a log file
              when a child process is terminated (main application will be interrupted by a
              SIGCHLD signal). So you have to implement an interrupt handler to handle
              this interrupt and do the corresponding action to it.
=============================================================================
Ahmed Ibrahim ,  © 2019 
