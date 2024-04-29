Code: #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_t;
  int cols_t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_pi:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    loop_ci:
    for (j = 0; j < 4940; j++) {
      nzval_t = nzval[j];
      cols_t = cols[j];
      if (cols_t == i) {
        sum += nzval_t * vec[j];
      }
    }
    out[i] = sum;
  }
}