#pragma ACCEL kernel

void ellpack(double nzval[4096],int cols[4096],double vec[64],double out[64])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  spmv_1:
  for (i = 0; i < 64; i++) {
    out[i] = ((double )0);
    spmv_2:
    for (j = 0; j < 64; j++) {
      out[i] += nzval[cols[j] + i * 64] * vec[j];
    }
  }
}