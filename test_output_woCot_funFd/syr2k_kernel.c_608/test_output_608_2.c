Code: #pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.

6. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.

7. `#pragma ACCEL PARALLEL FACTOR=auto{4}`: The loop is parallelized with a parallel factor of 4.

8. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.

9. `#pragma ACCEL TILE FACTOR=auto{80}`: Divide this loop into 80 parts.

10. `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.

11. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.

12. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.

13. `#pragma ACCEL PARALLEL FACTOR=auto{2}`: The loop is parallelized with a parallel factor of 2.

14. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.

15. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.

16. `#pragma ACCEL PARALLEL FACTOR=auto{4}`: The loop is parallelized with a parallel factor of 4.

17. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.

18. `#pragma ACCEL TILE FACTOR=auto{80}`: Divide this loop into 80 parts.

19. `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.

20. `#pragma ACCEL PIPELINE auto{}`: Automatically pipeline this loop.

21. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.

22. `#pragma ACCEL PARALLEL FACTOR=auto{5}`: The loop is parallelized with a parallel factor of 5.

23. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.

24. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.

25. `#pragma ACCEL PARALLEL FACTOR=auto{4}`: The loop is parallelized with a parallel factor of 4.

26. `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.

27. `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.

28. `#pragma ACCEL PARALLEL FACTOR=auto{5}`: The loop is parallelized with a parallel factor of 5.

#pragma ACCEL kernel

void kernel_syr2k(double alpha,double beta,double C[80][80],double A[80][60],double B[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B**T + alpha*B*A**T + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NKxNK
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 8