9. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

10. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

11. `#pragma ACCEL PARALLEL FACTOR=auto{5}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

12. `#pragma ACCEL PARALLEL FACTOR=auto{4}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

13. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

14. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

15. `#pragma ACCEL PARALLEL FACTOR=auto{6}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

16. `#pragma ACCEL PARALLEL FACTOR=auto{20}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

17. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

18. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

19. `#pragma ACCEL PARALLEL FACTOR=auto{5}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

20. `#pragma ACCEL PARALLEL FACTOR=auto{4}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

21. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

22. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

23. `#pragma ACCEL PARALLEL FACTOR=auto{6}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

24. `#pragma ACCEL PARALLEL FACTOR=auto{20}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

25. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

26. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

27. `#pragma ACCEL PARALLEL FACTOR=auto{5}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

28. `#pragma ACCEL PARALLEL FACTOR=auto{4}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

29. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

30. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

31. `#pragma ACCEL PARALLEL FACTOR=auto{6}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

32. `#pragma ACCEL PARALLEL FACTOR=auto{20}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

#pragma ACCEL kernel

void kernel_gemm(double alpha,double beta,double C[80][80],double A[80][60],double B[60][80])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'N'
// => Form C := alpha*A*B + beta*C,
//A is NIxNK
//B is NKxNJ
//C is NIxNJ
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{6}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{20}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
}