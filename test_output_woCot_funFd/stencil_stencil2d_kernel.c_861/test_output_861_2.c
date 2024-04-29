#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        result = ((filter[0] * orig[i - 4 + k]) + (filter[1] * orig[i - 3 + k]) + (filter[2] * orig[i - 2 + k]) + (filter[3] * orig[i - 1 + k]) + (filter[4] * orig[i + k]) + (filter[5] * orig[i + 1 + k]) + (filter[6] * orig[i + 2 + k]) + (filter[7] * orig[i + 3 + k]) + (filter[8] * orig[i + 4 + k]));
        sol[i + k - 4] = result;
      }
    }
  }
}