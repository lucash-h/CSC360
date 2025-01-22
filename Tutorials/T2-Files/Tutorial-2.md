# CSC360 Tutorial 2 // Spring 2025

## Getting started -- Here we go again!

Welcome to the second CSC360 tutorial.  Here, you are familiarizing yourself with Make and Linked Lists through a rather lengthy programming challenge.

If you are able to complete this challenge, you (vis-a-vis your programming skills) are in a great position to tackle Assignment 1.

## A note on Git and Tutorials:

It is recommended to create a repository under `~/CSC_360/<netlink_id>` and push your challenge code. If you have any trouble with this, it is a priority to sort out your access to the Gitlab. This, along with familiarity with Makefiles, should be your key takeaways from the first two tutorials. Issues with these may significantly impact your ability to submit Assignment 1.

## Challenge 1:

In this challenge, you will implement a very simplified version of a `history` feature similar to the one found in Unix shells, using a doubly linked list data structure. 
While the program is running, it will maintain a history of commands entered by the user and provide functionality to view and recall previous commands. 

You do not need to actually create the logic for *executing* the commands, beyond considering how they interface with the history and related doubly linked data structure. 

`simple_history.c` is a complete implementation to the depth of this challenge. The goal of this challenge is directed towards implementing the doubly linked list declared in `history_list.h` and defined in `history_list.c`. You will provide the implementations of the functions, as described below. In additional to finishing the doubly linked list, you are required to create a `makefile`.

Recall that `makefile`s can be run with `make`, the created files can be cleaned up with `make clean`.

**A note on memory management...** Avoid memory leaks, double frees and ensure proper handling of NULL pointers. Mistakes with any of these might cause tragic program behaviour at best, or undefined behaviour at worst. Remember, it's a good thing to know that your code doesn't work. Not knowing your code is broken might lead to security issues, or worse.

### Required Components & Behaviour:

#### 1. **History\* init_history()**

Purpose: Initialize a new history list

Returns: Pointer to newly allocated History structure

Parameters: None

Requirements:
- Allocate memory for History structure
- Initialize all fields to appropriate starting values
- Handle memory allocation failures

#### 2. **void add_to_history(History\* hist, const char\* command)**

Purpose: Add a new command to the history

Parameters:
- hist: Pointer to History structure
- command: String containing the command to add

Requirements:
- Skip empty commands
- Don't add duplicate of most recent command
- Maintain doubly linked list connections
- Enforce MAX_HISTORY_SIZE limit
- Handle memory allocation failures

#### 3. **char\* get_command_by_number(History\* hist, int number)**

Purpose: Retrieve a specific command by its number

Parameters:
- hist: Pointer to History structure
- number: Command number to retrieve

Returns: Newly allocated string containing the command, or NULL if not found

Requirements:
- Return NULL for invalid numbers
- Return a copy of the command string
- Handle memory allocation failures

#### 4. **void free_history(History\* hist)**

Purpose: Free all memory associated with history

Parameters: 
- hist: Pointer to History structure

Requirements:
- Free all HistoryNode structures
- Free all command strings
- Free the History structure itself
- Handle NULL pointer gracefully

#### 5. **Makefile**

Your makefile must link all the files to create a single executable.

Examples such as the one shared in Tutorial 2 may be used as a very strong basis. Additionally, it can't hurt to review to documentation [here](https://www.gnu.org/software/make/manual/make.html).

Some example code has been provided in `Tutorials/T2-Files` -- the same directory as this document. For best results, use this as a basis for your implementation. 

The tests below may be run manually in order to verify expected output:

Base case:

```Bash
Input:
> ls -l
> cd /home
> pwd
> history

Expected Output:
    1  ls -l
    2  cd /home
    3  pwd
```

Exit: program should terminate cleanly.

```Bash
Input:
> exit

Expected Output:
```

Some Edge Cases:

```Bash
Input:
> !0
Expected Output:
Invalid command 

Input:
> exitCommand
Expected Output:
Invalid command 

Input:
> history
(when no commands entered)
Expected Output:
(Empty history - no output)
```

Challenge yourself! Think of other edge cases that might misbehave and cause terrifying problems.