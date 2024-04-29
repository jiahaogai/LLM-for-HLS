#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int k1;
  int k2;
  int t;
  int mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopr:
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopc:
    for (c = 1; c < 8191; c++) {
      t = 0;
      mul = 1;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      loopk1:
      for (k1 = 0; k1 < 4; k1++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        loopk2:
        for (k2 = 0; k2 < 4; k2++) {
          t += mul * orig[r + (-1 + k1) * 8192 + (-1 + k2) * 64];
          mul *= filter[k1 * 4 + k2];
        }
      }
      sol[r * 8192 + c] = t;
    }
  }
}