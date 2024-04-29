Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  int d;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (t = 0; t < 8; t++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 32 + 2 * pad; j++) {
      inner:
      for (i = 0; i < 32 + 2 * pad; i++) {
        x = pad + i - t;
        y = pad + j;
        d = ((filter[0] * orig[x + y * 32]) + (filter[1] * orig[x + 1 + y * 32]) + (filter[2] * orig[x + 2 + y * 32])) + ((filter[3] * orig[x + (32 + 2 * pad) * 32]) + (filter[4] * orig[x + 1 + (32 + 2 * pad) * 32]) + (filter[5] * orig[x + 2 + (32 + 2 * pad) * 32])) + ((filter[6] * orig[x + (32 + 2 * pad) * 32 + 1]) + (filter[7] * orig[x + 1 + (32 + 2 * pad) * 32 + 1]) + (filter[8] * orig[x + 2 + (32 + 2 * pad) * 32 + 1]));
        sol[x + y * 32] = d;
      }
    }
  }
}