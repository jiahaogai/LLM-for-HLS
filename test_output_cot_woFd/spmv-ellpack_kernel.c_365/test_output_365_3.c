#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_tmp;
  int cols_tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  loopj:
  for (j = 0; j < 494; j++) {
    sum = ((double )0);
    loopi:
    for (i = 0; i < 490; i++) {
      nzval_tmp = nzval[i];
      cols_tmp = cols[i];
      if (cols_tmp == j) {
        sum += nzval_tmp * vec[cols_tmp];
      }
    }
    out[j] = sum;
  }
}