- `#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L5}`: Perform a reduction operation across loop iterations to compute `C` efficiently, utilizing specific hardware resources.
- `#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L1}`: Perform a reduction operation across loop iterations to compute `temp1` efficiently, utilizing specific hardware resources.
- `#pragma ACCEL PARALLEL reduction=temp5 FACTOR=auto{__PARA__L5}`: Perform a reduction operation across loop iterations to compute `temp5` efficiently, utilizing specific hardware resources.
- `#pragma ACCEL PARALLEL reduction=temp4 FACTOR=auto{__PARA__L4}`: Perform a reduction operation across loop iterations to compute `temp4` efficiently, utilizing specific hardware resources.
- `#pragma ACCEL PARALLEL reduction=temp3 FACTOR=auto{__PARA__L3}`: Perform a reduction operation across loop iterations to compute `temp3` efficiently, utilizing specific hardware resources.
- `#pragma ACCEL PARALLEL reduction=temp8 FACTOR=auto{__PARA__L8}`: Perform a reduction operation across loop iterations to compute `temp8` efficiently, utilizing specific hardware resources.
- `#pragma ACCEL PARALLEL reduction=temp7 FACTOR=auto{__PARA__L7}`: Perform a reduction operation across loop iterations to compute `temp7` efficiently, utilizing specific hardware resources.
- `#pragma ACCEL PARALLEL reduction=temp6 FACTOR=auto{__PARA__L6}`: Perform a reduction operation across loop iterations to compute `temp6` efficiently, utilizing specific hardware resources.

### Parameters:
  
#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      double temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp5 FACTOR=auto{__PARA__L5}
      double temp5 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp4 FACTOR=auto{__PARA__L4}
      double temp4 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp3 FACTOR=auto{__PARA__L3}
      double temp3 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp8 FACTOR=auto{__PARA__L8}
      double temp8 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp7 FACTOR=auto{__PARA__L7}
      double temp7 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp6 FACTOR=auto{__PARA__L6}
      double temp6 = 0.0;
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L5}
      for (j = 0; j < 60; j++) {
        temp2 = A[i][j] * B[j][k];
        temp5 += A[i][j] * temp8;
        temp4 += B[j][k] * temp7;
        temp3 += A[i][j] * B[j][k];
      }
      C[i][k] += alpha * temp1;
      C[i][k] += alpha * temp3;
      C[i][k] += beta * temp5;
      C[i][k] += beta * temp4;
    }
  }
//#pragma endscop
}