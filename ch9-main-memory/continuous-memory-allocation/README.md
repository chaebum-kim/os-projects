## How to run
1. Compile
```
make
```
2. Execute
```
./allocator <amount of memory>
```

## Commands
1. RQ : Request memory
```
allocator> RQ <process name> <amount of memory> <strategy[F][B][W]>

// F = first fit, B = best fit, W = worst fit
```

2. RL : Release memory
```
allocator> RL <process name>
```

3. C: Compact unused holes of memory into one region
```
allocator> C
```

4. STAT: Report the status of memory
```
allocator> STAT
```
