Code: #pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  err_new = ((double )10.) / 3.;
  err_old = err_new + 1.;
  iter = 0;
  while(err_old > err_new && err_new > tol && iter < max_iter){
     err_old = err_new;
//#pragma scop
     iter++;
     
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 0; i < 250; i++) {
       Y[i][0] = 0.0;
       Z[i][0] = 0.0;
       for (j = 1; j < 250; j++) {
         Y[i][j] = 0.0;
         Z[i][j] = 0.0;
         for (k = 0; k < 250; k++) {
           mul = A[i][k] * B[k][j];
           Y[i][j] += mul;
           Z[i][j] += mul * X[k][j];
         }
       }
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 0; i < 250; i++) {
       div = Z[i][0] / Y[i][0];
       X[i][0] = div;
       err_new += fabs(div);
       for (j = 1; j < 250; j++) {
         div = Z[i][j] / Y[i][j];
         X[i][j] = div;
         err_new += fabs(div);
       }
    }
//#pragma endscop
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:14: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘:’ token
    2 |   Explanation: Perform reduction operation for variable temp1 with a factor of 10, aggregating intermediate results in parallel.
      |              ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:1: error: stray ‘##’ in program
    4 | ##### dpoopt.c
      | ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:3: error: stray ‘##’ in program
    4 | ##### dpoopt.c
      |   ^~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:5: error: stray ‘#’ in program
    4 | ##### dpoopt.c
      |     ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void kernel_dpopt(double A[250][250],double B[250][250],double X[250][250],double Y[250][250],double Z[250][250],double tol,int max_iter)
{
  int i;
  int j;
  int k;
  int iter;
  double err_old;
  double err_new;
  double mul;
  double div;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  err_new = ((double )10.) / 3.;
  err_old = err_new +