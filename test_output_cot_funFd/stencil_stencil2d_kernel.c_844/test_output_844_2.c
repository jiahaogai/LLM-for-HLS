#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8191; j++) {
      buf[0] = orig[i - 1 + (j - 1) * 8192];
      buf[1] = orig[i + (j - 1) * 8192];
      buf[2] = orig[i + 1 + (j - 1) * 8192];
      buf[3] = orig[i - 1 + j * 8192];
      buf[4] = orig[i + j * 8192];
      buf[5] = orig[i + 1 + j * 8192];
      buf[6] = orig[i - 1 + (j + 1) * 8192];
      buf[7] = orig[i + (j + 1) * 8192];
      buf[8] = orig[i + 1 + (j + 1) * 8192];
      sol[i + j * 8192] = ((filter[0] * buf[0]) + (filter[1] * buf[1]) + (filter[2] * buf[2]) + (filter[3] * buf[3]) + (filter[4] * buf[4]) + (filter[5] * buf[5]) + (filter[6] * buf[6]) + (filter[7] * buf[7]) + (filter[8] * buf[8])) / 42;
    }
  }
}