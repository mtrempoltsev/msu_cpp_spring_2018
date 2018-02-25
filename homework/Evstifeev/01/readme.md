# Homework 1
Programs to sum matrix and measure their performance:
1) by rows
2) by columns
## How to run
Compile and run
```
make
```
## Results
On my MacBook air the results are:
1) 586302us by columns
2) 3034704us by rows

So, the performance of the algorithm on columns is five times faster than that on rows. 
This is due to the fact that, the first algorithm successively gets access to the elements by the pointer, while the second one skips over the pointers.
