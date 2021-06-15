## How to run
1. Compile
```
gcc -o shell shell.c
```
2. Execute
```
./shell
```

## Operators
1. Run command in the background
```
osh>cat shell.c &
```

2. Redirect input
```
osh>sort < in.txt
```

3. Redirect output
```
osh>ls > out.txt
```

4. Chain commands
```
osh>ls -l | less
```
