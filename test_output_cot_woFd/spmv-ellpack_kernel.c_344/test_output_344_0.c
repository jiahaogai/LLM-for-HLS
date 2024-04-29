#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nz;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    int tmp_begin = cols[i];
    int tmp_end = cols[i + 1];
    spmv_2:
    for (j = tmp_begin; j < tmp_end; j++) {
      nz = nzval[j];
      sum += nz * vec[cols[j]];
    }
    out[i] = sum;
  }
}