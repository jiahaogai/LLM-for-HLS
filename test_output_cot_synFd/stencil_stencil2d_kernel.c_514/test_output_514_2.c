#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      buf = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        buf += filter[k] * orig[i + (-4 + k) * 8192];
      }
      sol[i * 8192 + j] = buf;
    }
  }
}