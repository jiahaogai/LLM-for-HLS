

7. For the second loop:
    - Don't automatically pipeline this loop.

8. For tiling:
    - Process this loop in its original, full form without breaking it into smaller chunks.

9. For parallelization with a factor of 2:
    - Run the iterations of this loop in parallel with a parallel factor of 2.

10. For the inner loop (first usage):
    - Run the iterations of this loop one after the other, not in parallel.

11. For the inner loop (second usage):
    - Run the iterations of this loop in parallel with a parallel factor of 2.

12. For the third loop:
    - Don't automatically pipeline this loop.

13. For tiling:
    - Process this loop in its original, full form without breaking it into smaller chunks.

14. For parallelization with a factor of 2:
    - Run the iterations of this loop in parallel with a parallel factor of 2.

15. For the fourth loop:
    - Don't automatically pipeline this loop.

16. For tiling:
    - Process this loop in full form with a tile size of 128.

17. For parallelization with a factor of 2:
    - Run the iterations of this loop in parallel with a parallel factor of 2.

18. For the fifth loop:
    - Don't automatically pipeline this loop.

19. For tiling:
    - Process this loop in full form with a tile size of 4.

20. For parallelization with a auto-parallel factor:
    - Automatically parallelize this loop with a parallel factor of 2.

21. For the sixth loop:
    - Don't automatically pipeline this loop.

22. For tiling:
    - Process this loop in full form with a tile size of 4.

23. For parallelization with a auto-parallel factor:
    - Automatically parallelize this loop with a parallel factor of 2.

24. For the seventh loop:
    - Don't automatically pipeline this loop.

25. For tiling:
    - Process this loop in full form with a tile size of 4.

26. For parallelization with a auto-parallel factor:
    - Automatically parallelize this loop with a parallel factor of 2.

27. For the eighth loop:
    - Don't automatically pipeline this loop.

28. For tiling:
    - Process this loop in full form with a tile size of 4.

29. For parallelization with a auto-parallel factor:
    - Automatically parallelize this loop with a parallel factor of 2.

30. For the ninth loop:
    - Don't automatically pipeline this loop.

31. For tiling:
    - Process this loop in full form with a tile size of 4.

32. For parallelization with a auto-parallel factor:
    - Automatically parallelize this loop with a parallel factor of 2.

33. For the function `kernel_jacobi_1d`:
    - Automatically pipeline this kernel.

#pragma ACCEL kernel

void kernel_jacobi_1d(int tsteps,int n,double A[120],double B[120])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 40; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (i = 1; i < 120 - 1; i++) {
      B[i] = 0.33333 * (A[i - 1] + A[i] + A[i + 1]);
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (i = 1; i < 120 - 1; i++) {
      A[i] = 0.33333 * (B[i - 1] + B[i] + B[i + 1]);
    }
  }
//#pragma endscop
}
