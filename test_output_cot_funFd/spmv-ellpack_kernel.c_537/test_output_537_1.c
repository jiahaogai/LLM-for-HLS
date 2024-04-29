#pragma ACCEL kernel

void ellpack(double nzval[256],int cols[256],double vec[16],double out[16])
{
  int i;
  int j;
  for (i = 0; i < 16; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 16; j++) {
    int tmp_idx;
    double tmp_val;
    tmp_idx = cols[j];
    tmp_val = nzval[j];
    out[tmp_idx] += tmp_val * vec[j];
  }
}