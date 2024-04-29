#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 1; j < 33; j++) {
      idx = i * 32 + j;
      sol[idx] = 0.0;
      x = orig[idx] - filter[1];
      y = filter[4];
      sol[idx] += x * y;
      x = orig[idx] - filter[2];
      y = filter[5];
      sol[idx] += x * y;
      x = orig[idx] - filter[0];
      y = filter[6];
      sol[idx] += x * y;
      x = orig[idx] - filter[7];
      y = filter[8];
      sol[idx] += x * y;
      x = orig[idx] - filter[9];
      y = filter[8];
      sol[idx] += x * y;
    }
  }
}