#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nz;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    int_1:
    for (j = 0; j < 32; j++) {
      nz = nzval[i * 32 + j];
      vec_1:
      for (j = 0; j < 32; j++) {
        nz = nzval[i * 32 + j] * vec[cols[i * 32 + j]];
        sum += nz;
      }
    }
    out[i] = sum;
  }
}