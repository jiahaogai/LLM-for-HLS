#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][240],double A[200][200],double B[200][240])
{
  int m;
  int n;
  int p;
  int q;
  int x_col;
  int x_row;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (m = 0; m < 200; m++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (n = 0; n < 240; n++) {
      x_col = n;
      x_row = m;
      mult = 0.0;
      
#pragma ACCEL PARALLEL reduction=mult FACTOR=auto{1}
      inner:
      for (p = 0; p < 200; p++) {
        mult += A[x_row][p] * B[p][x_col];
      }
      C[x_row][x_col] = mult * alpha + C[x_row][x_col] * beta;
    }
  }
}