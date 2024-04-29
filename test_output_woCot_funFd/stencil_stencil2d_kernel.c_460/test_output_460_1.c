#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4 * 9;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 4 + 8; i < 8192 - 8 - 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 4 + 8; j < 8192 - 8 - 4; j++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (k = 0; k < 9; k++) {
        t += filter[k] * orig[i + ((k - 4) * 8192 / 4)];
      }
      sol[i * 8192 + j] = t;
    }
  }
}