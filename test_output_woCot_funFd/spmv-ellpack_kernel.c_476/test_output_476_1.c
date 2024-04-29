#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_tmp;
  int cols_tmp;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  ellpack_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    ellpack_2:
    for (j = 0; j < 9; j++) {
      nzval_tmp = nzval[i * 9 + j];
      cols_tmp = cols[i * 9 + j];
      sum += nzval_tmp * vec[cols_tmp];
    }
    out[i] = sum;
  }
}