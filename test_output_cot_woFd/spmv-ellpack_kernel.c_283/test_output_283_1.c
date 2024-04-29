#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_tmp;
  int cols_tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{494}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_ellpack_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    loop_ellpack_2:
    for (j = 0; j < 16; j++) {
      nzval_tmp = nzval[i * 16 + j];
      cols_tmp = cols[i * 16 + j];
      sum += nzval_tmp * vec[cols_tmp];
    }
    out[i] = sum;
  }
}