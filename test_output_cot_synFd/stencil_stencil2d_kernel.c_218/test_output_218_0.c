#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int bound;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (c = 1; c < 8191; c++) {
      bound = 8191 - c;
      sol[r * 8192 + c] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 9; i++) {
        j = bound * i / 8;
        sol[r * 8192 + c] += filter[i] * orig[r * 8192 + j];
      }
    }
  }
//#pragma endscop
}