#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8186; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -4; k <= 4; k++) {
        tmp += filter[k + 4] * orig[i + k * 8192];
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}