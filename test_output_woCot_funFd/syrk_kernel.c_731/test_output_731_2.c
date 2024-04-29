Code: #pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

10. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

11. `#pragma ACCEL PARALLEL FACTOR=auto{8}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

12. `#pragma ACCEL PARALLEL FACTOR=auto{40}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

13. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

14. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

15. `#pragma ACCEL PARALLEL FACTOR=auto{8}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

16. `#pragma ACCEL PARALLEL FACTOR=auto{8}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

17. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

18. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

19. `#pragma ACCEL PARALLEL FACTOR=auto{4}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

20. `#pragma ACCEL PARALLEL FACTOR=auto{40}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

21. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

22. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

23. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

24. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

25. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

26. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

27. `#pragma ACCEL PARALLEL FACTOR=auto{8}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

28. `#pragma ACCEL PARALLEL FACTOR=auto{8}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

29. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

30. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

31. `#pragma ACCEL PARALLEL FACTOR=auto{4}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

32. `#pragma ACCEL PARALLEL FACTOR=auto{40}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

#pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
//BLAS PARAMS
//TRANSA = 'N'
//TRANSB = 'T'
// => Form C := alpha*A*A**T + beta*C,
//A is NIxNK
//C is NIxNI
//K is NK
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{