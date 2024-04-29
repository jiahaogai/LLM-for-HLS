#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 8176; j++) {
      idx = (i * 8192) + j;
      sol[idx] = ((filter[0] * orig[idx - 8192]) + (filter[1] * orig[idx - 8176]) + (filter[2] * orig[idx - 8172]) + (filter[3] * orig[idx - 8168]) + (filter[4] * orig[idx - 8164]) + (filter[5] * orig[idx - 8160]) + (filter[6] * orig[idx - 8156]) + (filter[7] * orig[idx - 8152]) + (filter[8] * orig[idx - 8148]) + (filter[9] * orig[idx - 8144])) / 40.0;
    }
  }
}