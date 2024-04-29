#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      for (k = 0; k < 9; k++) {
        x = i - 4 + ((k % 3) - 1);
        y = j - 4 + (k / 3);
        t += filter[k] * orig[x * 8192 + y];
      }
      sol[i * 8192 + j] = t;
    }
  }
}