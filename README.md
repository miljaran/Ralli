# Ralli

## Description
This is a final project for the basic course in C programming in Aalto university. The program keeps track on rally drivers and their times. The user can add new drivers and update their time. The current game situation can be printed so that the fastest driver is in the top of the list. If two or more drivers have the same time they are printed in alphabetical order. The program can also save the current game situation in a file or read a situation from a file.

## Running the program
The program can be compiled with the command `gcc -o ralli projekti.c` and then run with the command `./ralli`.

## Commands
`A name garage` adds a new player with the given name and garage\
`L` prints the current situation\
`U name hours minutes seconds` adds the time to the given driver\
`W filename` saves current situation in a file with the given name\
`O filename` replaces the current situation with the one read from the given file\
`Q` quits the program

## Format of the files
The program can read data from files in the following format:\
`name, garage: x tuntia, y minuuttia, z sekuntia`
where `name` is the name of the driver, `garage` is their garage, `x` is hours, `y` is minutes and `z` is seconds.
