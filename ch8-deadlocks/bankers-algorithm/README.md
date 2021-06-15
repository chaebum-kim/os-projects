### Follwing commands are available:

1. RQ: Request resources<br>
   RQ customer_num resources<br>
   eg. RQ 0 3 1 2 1

2. RL: Release resources<br>
   RL customer_num resources<br>
   eg. RL 4 1 2 3 1

3. \*: Print out the values of the available, maximum, allocation, and need arrays

4. exit: Exit the program

### Test Scenario

0. make
1. ./main 13 10 6 9
2. RQ 0 3 0 1 4 -> Granted
3. RQ 1 2 2 1 0 -> Granted
4. RQ 2 3 1 2 1 -> Granted
5. RQ 3 0 5 1 0 -> Granted
6. RQ 4 4 2 1 2 -> Granted
7. RQ 0 2 0 0 0 -> Denied due to the lack of available resources
8. RQ 0 1 0 0 2 -> Denied because it leaves the system in an unsafe state
9. exit
