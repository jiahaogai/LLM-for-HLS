#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nz;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 5; j++) {
      nz = nzval[i * 5 + j];
      sum += nz * vec[cols[i * 5 + j]];
    }
    out[i] = sum;
  }
}