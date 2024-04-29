#pragma ACCEL kernel

void stencil(double A[25][25],double B[25][25])
{
  int r;
  int q;
  int c;
  int p;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (q = 0; q < 25; q++) {
      mult = 0.0;
      for (p = 0; p < 25; p++) {
        mult += A[r][p] * B[p][q];
      }
      A[r][q] = mult;
    }
  }
}