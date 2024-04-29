#pragma ACCEL kernel

void ellpack(double nzval[4096],int cols[4096],double vec[64],double out[64])
{
  int i;
  int j;
  double sum;
  double val;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  spmv_1:
  for (i = 0; i < 64; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 64; j++) {
      val = nzval[cols[j] + i * 64];
      sum += val * vec[j];
    }
    out[i] = sum;
  }
}