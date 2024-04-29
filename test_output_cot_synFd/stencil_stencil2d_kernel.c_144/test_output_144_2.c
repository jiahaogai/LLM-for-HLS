#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8186; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        x = k + j;
        if (x < 1 || x > 8186) {
          continue;
        }
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
	for (y = -4; y <= 4; y++) {
          int offset = (x - 1) + (y + 4) * 8192;
          t += filter[k + 4] * orig[offset];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}