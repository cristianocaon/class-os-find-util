# Find command

Code developed for the operating system class (CS 4352), with professor Dr. Yong Chen at Texas Tech University.

The provided code implements the ```find``` command provided in UNIX operating systems.

## Functionalities

* ```./cfind``` runs on the current directory
* ```./cfind {dir}``` runs on specified directory
* ```./cfind {dir} -n {target}``` searches for given target name
* ```./cfind {dir} -inum {target}``` searches for given target inumber
* ```./cfind {dir} -mmin {target}``` searches for modified time of file. ```-``` searches for less than time, ```+``` searches for more than time, and without signal searches for specific time

When running the command with any of the flags, ```-delete``` can be added as a last argument to delete the found files. ```cfind_script.sh``` does not provide log output files for this case for safety.

The ```testdir``` directory is provided only to test the functionality of the command and to generate consistent results.
