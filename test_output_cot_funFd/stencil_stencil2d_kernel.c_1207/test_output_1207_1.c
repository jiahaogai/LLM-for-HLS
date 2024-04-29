#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int tid;
  int row;
  int col;
  int flatten_i;
  int flatten_j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner_loop:
    for (j = 8; j < 8192; j += 8) {
      tid = i * 8192 + j;
      row = i - 8 + 1;
      col = j - 8 + 1;
      flatten_i = i / 64 + 1;
      flatten_j = j / 64 + 1;
      sol[tid] = ((filter[0] * orig[tid - 8 - 8192]) + (filter[1] * orig[tid - 8 - 1]) + (filter[2] * orig[tid - 8]) + (filter[3] * orig[tid - 8 + 1]) + (filter[4] * orig[tid - 8 + 8192]) + (filter[5] * orig[tid - 1]) + (filter[6] * orig[tid]) + (filter[7] * orig[tid + 1]) + (filter[8] * orig[tid + 8 + 8192])) / 64.0;
    }
  }
}