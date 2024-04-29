#pragma ACCEL kernel

void stencil(double A[25][25],double B[25][25])
{
  int r;
  int c;
  int i;
  int j;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 0; c < 25; c++) {
      mult = 0.0;
      for (i = 0; i < 25; i++) {
        for (j = 0; j < 25; j++) {
          mult += A[i][j] * B[j][c];
        }
      }
      A[r][c] = mult;
    }
  }
}