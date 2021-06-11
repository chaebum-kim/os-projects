# Table of Contents
| No | Name | Description |
|---|---|---|
|3.18|1-zombie.c|A program that forks a child process that ultimately becomes a zombie process.|
|3.19|2-time_pipes.c <br>2-time_shm.c|A program that determines the amount of time necessary <br>to run a command from the command line.|
|3.20|3-pid-manager|An API for obtaining and releasing a pid.|
|3.21|4-collatz.c|A program that generates collatz sequence given a positive number.|
|3.22|5-collatz_shm.c|A program that generates collatz sequence given a positive number using shared memory.|
|3.23|6-quoteofday|A server that listens to port 6017 and delivers quote of the day.|
|3.24|7-haiku|A server that listens to port 5575 and delivers a haiku.|
|3.25|8-echo|An echo server.|
|3.26|9-reverse.c| A program in which one process sends a string message to a second process, <br> and the second process reverses the case of each character in the message <br> and sends it back to the first process.|
|3.27|10-filecopy.c|A simple file-copying program using ordinary pipes.|


## 1-zombie.c
1. Compile
``` 
make zombie
```
2. Execute
```
// Run the program in the background
./zombie &

// Determine whether the child process is a zombie process
ps -l

// Terminate the parent process
kill -9 <parent process id>
```

## 2-time_pipes.c
1. Compile
```
make time_pipes
```
2. Execute
```
./time_pipes <command>
```

## 2-time_shm.c
1. Compile
```
make time_shm
```
2. Execute
```
./time_shm <command>
```

## [3-pid-manager](https://github.com/chaebum-kim/os-projects/new/master/os_problems/chapter3/3-pid-manager)
1. Compile
```
make
```
2. Execute
```
./test
```

## 4-collatz.c
1. Compile
```
make collatz
```
2. Execute
```
./collatz <positive integer>
```

## 5-collatz_shm.c
1. Compile
```
make collatz_shm.c
```
2. Execute
```
./collatz_shm <positive integer>
```

## 9-reverse.c
1. Compile
```
make reverse
```
2. Execute
```
./reverse
```

## 10-filecopy.c
1. Compile
```
make filecopy
```
2. Execute
```
./filecopy hello.txt hello2.txt
```





