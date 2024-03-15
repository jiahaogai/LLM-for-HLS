#include <math.h>
#pragma ACCEL kernel

void kernel_correlation(double float_n,double data[100][80],double corr[80][80],double mean[80],double stddev[80])
{
  int i;
  int j;
  int k;
  double eps = 0.1e-10;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
/* The following in an inelegant but usual way to handle
         near-zero std. dev. values, which below would cause a divide by zero.
         (Application developers responsibility to avoid this condition!) */
    stddev[j] = (stddev[j] <= eps?1.0 : stddev[j]);
  }
/* Center and reduce the column vectors. */
  
#pragma ACCEL PIPELINE auto{__PIPE__L4}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
  for (i = 0; i < 100; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
    for (j = 0; j < 80; j++) {
      data[i][j] -= mean[j];
      data[i][j] /= sqrt(float_n) * stddev[j];
    }
  }
/* Calculate the m * m correlation matrix. */
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
  for (i = 0; i < 80; i++) {
    corr[i][i] = 1.0;
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    for (j = i + 1; j < 80; j++) {
      corr[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (k = 0; k < 100; k++) {
        corr[i][j] += data[k][i] * data[k][j];
      }
      corr[j][i] = corr[i][j];
    }
  }
}