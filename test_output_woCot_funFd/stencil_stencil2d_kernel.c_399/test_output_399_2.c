#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int bound = 32;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -bound; k < bound + 1; k++) {
        if ((k != 0)) {
          t += filter[((bound + 1) + k)] * orig[i + k];
        }
      }
      sol[j] = t;
    }
  }
}