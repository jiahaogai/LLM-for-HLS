Code: #pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

10. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

11. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

12. `#pragma ACCEL PARALLEL FACTOR=auto{2}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

13. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

14. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

15. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

16. `#pragma ACCEL PIPELINE auto{off}` - Do not pipeline the loops.

17. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

18. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.
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
//C is NIxNJ
//K is NK
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{5}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * A[j][k];
      }
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

10. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

11. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

12. `#pragma ACCEL PARALLEL FACTOR=auto{2}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

13. `#pragma ACCEL PIPELINE auto{}` - Automatically pipeline the loops for optimization.

14. `#pragma ACCEL TILE FACTOR=auto{1}` - Divide the loop into smaller parts with a factor that is automatically determined for optimization.

15. `#pragma ACCEL PARALLEL FACTOR=auto{1}` - Execute loop iterations concurrently with a factor that is automatically determined for optimization.

16. `#pragma ACCEL PI