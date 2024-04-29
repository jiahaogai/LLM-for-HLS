#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      flatten_row = i * 256;
      row = flatten_row + j;
      idx = row * 256 + j;
      val = ((filter[0] * orig[idx]) + (filter[1] * orig[idx + 1]) + (filter[2] * orig[idx + 2])) + ((filter[3] * orig[idx + 256]) + (filter[4] * orig[idx + 257]) + (filter[5] * orig[idx + 258])) + ((filter[6] * orig[idx + 512]) + (filter[7] * orig[idx + 513]) + (filter[8] * orig[idx + 514]));
      sol[row] = val;
    }
  }
}