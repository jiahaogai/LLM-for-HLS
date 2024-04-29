### Parameters:
- `alpha`: double  
- `beta`: double  
- `C`: double[80][80]  
- `A`: double[80][60]  

### Local Variables:
- `i`: int  
- `j`: int  
- `k`: int  
- `tmp`: double  
  
### Global Variables Accessed:
- `C`  
- `A`  

#pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
  double tmp;
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
    for (j = 0; j < 80; j++) {
      tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
      for (k = 0; k < 60; ++k) {
        tmp += A[i][k] * A[j][k];
      }
      C[i][j] = tmp;
    }
  }
  
#pragma endscop
}