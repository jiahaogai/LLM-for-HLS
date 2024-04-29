Code: ### Array Declarations:
- `double C[60][80]`: Multidimensional array with element type `double` and size 60x80.
- `double A[60][60]`: Multidimensional array with element type `double` and size 60x60.
- `double B[60][80]`: Multidimensional array with element type `double` and size 60x80.

### Parameter List:
- `double alpha`: Parameter with element type `double`.
- `double beta`: Parameter with element type `double`.

### Local Variables:
- `int i`: Loop counter with type `int` and range 0 to 59.
- `int j`: Loop counter with type `int` and range 0 to 79.
- `int k`: Loop counter with type `int` and range 0 to 59.
- `double temp1`: Parameter with element type `double`.
- `double temp2`: Parameter with element type `double`.

### Intrinsic Functions Calls:
- `scanf`: Function with no intrinsic function but called as an intrinsic function.
- `printf`: Function with no intrinsic function but called as an intrinsic function.

### Function Body:
 
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double temp1;
  double temp2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      temp1 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{20}
      for (k = 0; k < 60; ++k) {
        temp1 += A[i][k] * B[k][j];
      }
      C[i][j] = temp1;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      C[i][j] *= alpha;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{60}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{80}
    for (j = 0; j < 80; j++) {
      C[i][j] += beta * A[i][j];
    }
  }
}