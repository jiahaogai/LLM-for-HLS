#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
  double sum;
  double nzval_tmp;
  int cols_tmp;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  spmv_1:
  for (i = 0; i < 49; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 494; j++) {
      nzval_tmp = nzval[j];
      cols_tmp = cols[j];
      if (cols_tmp == i) {
        sum += nzval_tmp * vec[cols_tmp];
      }
    }
    out[i] = sum;
  }
}