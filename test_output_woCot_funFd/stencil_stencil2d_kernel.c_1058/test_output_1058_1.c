#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8; j++) {
      t = 0;
      inner:
      for (k = -4; k < 5; k++) {
        if ((i + k) < 0 || (j + k) < 0 || (i + k) > 79 || (j + k) > 79) 
          continue;
        t += filter[pt + k] * orig[(i + k) * 64 + (j + k)];
      }
      sol[i * 64 + j] = t;
    }
  }
}