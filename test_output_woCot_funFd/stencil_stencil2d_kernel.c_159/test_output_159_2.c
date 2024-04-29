#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 1; j < 8191; j++) {
      s = 0.0;
      idx = -4;
      while (idx <= 4) {
        s += ((double )filter[++idx]) * orig[i + idx];
      }
      sol[j] = s;
    }
    sol[8192 - 1] = ((-1 * 0.5) * sol[0]) + ((1.0 * 0.5) * sol[1]);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 8190; j >= 2; j--) {
      sol[j] = ((-1 * 0.5) * sol[j]) + ((1.0 * 0.5) * sol[j - 1]);
    }
    sol[0] = ((1.0 * 0.5) * sol[1]) + ((-1.0 * 0.5) * sol[0]);
  }
}