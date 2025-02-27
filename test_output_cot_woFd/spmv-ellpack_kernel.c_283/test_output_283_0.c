#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_t;
  int cols_t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{494}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_ellpack_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    loop_ellpack_2:
    for (j = 0; j < 16; j++) {
      nzval_t = nzval[i * 16 + j];
      cols_t = cols[i * 16 + j];
      sum += nzval_t * vec[cols_t];
    }
    out[i] = sum;
  }
}