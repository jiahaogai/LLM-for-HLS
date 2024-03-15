- "Automatically parallelize this loop with a factor of 2" - for the line `#pragma ACCEL PARALLEL FACTOR=auto{2}`.

**pearson_correlation_part1.c**

```
 #include <math.h>
#pragma ACCEL kernel

void kernel_correlation(double float_n,double data[100][80],double corr[80][80],double mean[80],double stddev[80])
{
  int i;
  int j;
  int k;
  double eps = 0.1;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 0; j < 80; j++) {
    mean[j] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (i = 0; i < 100; i++) {
      mean[j] += data[i][j];
    }
    mean[j] /= float_n;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (j = 0; j < 80; j++) {
    stddev[j] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 100; i++) {
      stddev[j] += pow(data[i][j] - mean[j],(double )2);
    }
    stddev[j] /= float_n;
    stddev[j] = sqrt(stddev[j]);
    stddev[j] = (stddev[j] <= 1.0e-10 ? 1.0 : stddev[j]);
  }
// Matrix-matrix multiplication
// AxB, A: mean of data, B: data
// Note:
// Need to use "inner" layout for B to get good performance.
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (j = 0; j < 80; j++) {
      corr[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (k = 0; k < 100; k++) {
        corr[i][j] += (data[k][i] - mean[i]) * (data[k][j] - mean[j]);
      }
      corr[i][j] /= stddev[i] * stddev[j];
    }
  }
}
