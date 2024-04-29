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
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 64; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (x = -4; x < 5; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        for (y = -4; y < 5; y++) {
          t += orig[i + x + ((y + 4) * 64)] * filter[x + 4];
        }
      }
      sol[i + j] = t;
    }
  }
}