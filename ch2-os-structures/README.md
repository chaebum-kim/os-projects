
## Description
|Name|Description|
|---|---|
|proc_jiffies.c|kernel module that creates a /proc file named /proc/jiffies that <br/>reports the current value of jiffies when the proc/jiffies file is read|
|proc_seconds.c|kernel module that creates a /proc file named /proc/seconds that <br/>reports the number of elapsed seconds since the kernel module was loaded <br/>when the proc/seconds file is read |


## How to run

1. Compile the source code

```c
make

//The compilation should produce several files.
//The file with .ko extension represents the compiled kerneml module.
```


2. Load the kernel module
```c
sudo insmod proc_jiffies.ko

//To check whether the module has loaded, enter the lsmod command and search for the module proc_jiffies.
```


3. Run the command
```c
cat /proc/jiffies
```

4. Remove the kernel module
```
sudo rmmod proc_jiffies
```
