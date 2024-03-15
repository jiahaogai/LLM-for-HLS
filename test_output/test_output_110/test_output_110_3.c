

7. Mark the following function as a kernel:
   - Use: `#pragma ACCEL kernel`

8. Implement a loop that is parallelized auto{__PARA__L2}:
   - Use: `#pragma ACCEL PIPELINE auto{off}`
   - Use: `#pragma ACCEL TILE FACTOR=auto{1}`
   - Use: `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}`

9. Implement the loop below by parallelizing the reduction operation with a factor of 1:
   - Use: `#pragma ACCEL PARALLEL reduction=y FACTOR=auto{1}`

 **>  Y = sum( A )
 **>  A = input
 **>  Y = 0.0

void kernel_gemver(int n,double alpha,double beta,double A[400][400],double u1[400],double v1[400],double u2[400],double v2[400],double w[400],double x[400],double y[400],double z[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    double tmp_z = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * u1[j];
      tmp_x += A[i][j] * v1[j];
    }

    y[i] = beta * y[i] + alpha * tmp;
    
#pragma ACCEL PARALLEL reduction=tmp_x FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp_x += A[i][j] * u2[j];
    }

    x[i] = beta * x[i] + alpha * tmp_x;
    
#pragma ACCEL PARALLEL reduction=tmp_y FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      tmp_y += A[i][j] * x[j];
    }

    z[i] = beta * z[i] + alpha * tmp_y;
    
#pragma ACCEL PARALLEL reduction=tmp_z FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      tmp_z += A[i][j] * v2[j];
    }

    w[i] = beta * w[i] + alpha * tmp_z;
  }
}
