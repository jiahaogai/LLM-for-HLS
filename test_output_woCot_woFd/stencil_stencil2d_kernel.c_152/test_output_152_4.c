#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8; j < 8184; j += 8) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (x = -1; x <= 1; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (y = -1; y <= 1; y++) {
          t += filter[((y + 1) * 3) + (x + 1)] * orig[i + y + 1][j + x + 1];
        }
      }
      sol[i][j] = t;
    }
  }
}