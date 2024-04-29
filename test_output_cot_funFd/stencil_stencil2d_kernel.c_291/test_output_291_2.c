#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int bound;
  int flatten_bound;
  int range_l;
  int range_u;
  int step;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  bound = 8192;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  flatten_bound = 128;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  range_l = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{64}
  range_u = 64;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  step = 1;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  for (i = 1; i < 64; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128; j++) {
      idx = i * 128 + j;
      sol[idx] = ((filter[0] * orig[idx - 1 - 128]) + (filter[1] * orig[idx - 1]) + (filter[2] * orig[idx - 1 + 128]) + (filter[3] * orig[idx + 1 - 128]) + (filter[4] * orig[idx + 1]) + (filter[5] * orig[idx + 1 + 128]) + (filter[6] * orig[idx - 128]) + (filter[7] * orig[idx + 0]) + (filter[8] * orig[idx + 128])) / 42;
    }
  }
//#pragma endscop
}