# CSC360 Tutorial 1 // Spring 2025

## Getting started

Welcome to the first CSC360 tutorial.  Most of these tutorials will focus on assignment support, but this first tutorial will allow you to familiarize yourself with the tools we'll be using in this course.  Tutorials are not graded, so feel free to experiment.

## GitLab

The code for our tutorials and assignments can be found at https://gitlab.csc.uvic.ca/courses/2025011/CSC360_COSI/ .  You have a repository there, at:

`gitlab.csc.uvic.ca/courses/2025011/CSC360_COSI/assignments/<YOUR NETLINK ID>` 

Go there now and take a look - most of the folders are empty, but the
`T1-Files/` folder has some files in it (including this file, `Tutorial-1.md`).

## Linux Lab

Our programming environment for the course will be on the UVic CSC Linux Servers, use of which is described in the Tutorial-1 Slides. 

## Configure Git

Tutorial-1 Slides discuss connecting to git. You may also wish to conduct additional configuration to tell git who you are: 

```
git config --global user.name <YOUR NETLINK ID>
git config --global user.email <YOUR EMAIL ADDRESS>
```

## Clone your repository

On the linux lab computers:

Locate the CLONE button in GitLab for the course repository, and copy the url under the **Clone with HTTPS** (or SSH) option.  Clone your repo into the Linux Lab with the `git clone` command.

## Challenge 1:

Write a simple hello-world program.  Call it `hello_world.c`, and compile and run it to make sure it works.  To make sure there are no syntax errors or other problems, compile it with warning flags set:

`gcc -Wall -Werror -std=c18 -o hello_world hello_world.c`

Once you have it working, use `git add` to set your new file to be tracked by git.  Write a `git commit` message (make it something descriptive) and then `git push` your changes back to GitLab.

Make sure your push worked!  Go to GitLab in a web browser and check that your new file(s) are there. 

Remember we can't mark your work if it's not in GitLab, so get used to this commit-and-push procedure.

## Challenge 2:

In your `Tutorials/T1-Files` directory, you'll find a text file called `input_text.txt`.  Open it and look it over - it describes the task you need to do (You need to write a short program that replicates the behaviour of the `wc -w` unix utility).

Give this program a try!  If you find yourself having a lot of trouble remembering your C syntax, you might want to set aside some time to refresh your knowledge before the first assignment.

If you try Challenge 2, remember to commit and push your changes!

## If things go wrong:

You may accidently write an infinite loop or otherwise use up all the resources available to you, and you may find that the system becomes unresponsive.  It's important that we're able to recover from these sorts of situations, which often arise when you start playing with fundamental parts of the operating system.

Remember that you can stop a running program using **CTRL-c**.

## Caching your Git credentials

Sometimes it's irritating to type your username and password each time you interact with GitLab. If you do not wish to configure ssh, you may instead choose to get git to remember your credentials for a short time.  If you want to cache your credentials for 15 minutes, use the default command:

`git config --global credential.helper cache`

You may want to do so for longer than the default period; the following command will set the timeout to one hour:

`git config --global credential.helper "cache --timeout=3600"`
