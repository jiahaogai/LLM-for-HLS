#pragma ACCEL kernel

void ellpack(double nzval[2304],int cols[1008],double vec[16],double out[16])
{
  int i;
  int j;
  double sum;
  double ELEM_FACTOR = 1.0;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  spmv_1:
  for (i = 0; i < 16; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 4; j++) {
      sum += nzval[cols[i + (j << 4)]] * vec[j];
    }
    out[i] = sum * ELEM_FACTOR;
  }
}