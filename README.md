# Counting-Prime-Numbers
This parallel C program to count prime numbers between a given range (x, y) using MPI_Send and MPI_Receive. Each process calculates primes in its assigned sub-range, and the master process aggregates the counts. Input: lower bound x and upper bound y. Output: total prime count and counts per process.

You must use MPI_SEND & MPI_RECV ONLY on this problem

### Input
- Lower bound number x
- Upper bound number y
### Output
- Count of prime numbers occurring between x and y
- Count of prime numbers occurring in each process.

### Example:
#### Input:
X = 1
Y = 100
#### Output
“Total number of prime numbers is: 25”
“Total number of prime numbers in P1 is: 11”
“Total number of prime numbers in P2 is: 7”
“Total number of prime numbers in P3 is: 7”

## Parallelization Scenario
### Master Process:
- Calculate the sub range size r=(y-x)/p
- Note that p is the number of processes.
- Broadcast x and r to each slave process using MPI_Send.
- Receive sub count from each slave process using MPI_Receive.
- Print total count of primes between x and y.
### Slave Process:
- Receive x and r through the MPI_Receive.
- Calculate the lower bound a and upper bound b according to its rank.
- Count primes in its sub range (between a and b).
- Print the partial count
- Send this partial count to the master process using the MPI_Send.
