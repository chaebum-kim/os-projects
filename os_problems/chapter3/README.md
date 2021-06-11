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





