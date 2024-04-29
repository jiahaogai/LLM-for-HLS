For more information, see `ref_impl.c`.

#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nz;
  double v;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    int tmp_begin = 0 + i * 16;
    int tmp_end = 16 + i * 16;
    spmv_2:
    for (j = tmp_begin; j < tmp_end; j++) {
      nz = nzval[j];
      v = vec[cols[j] - 1];
      sum += nz * v;
    }
    out[i] = sum;
  }
}