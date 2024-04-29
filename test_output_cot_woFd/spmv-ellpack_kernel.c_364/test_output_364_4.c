#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_t;
  int cols_t;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  sum = ((double )0);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 64; i++) {
    sum += nzval[i] * vec[cols[i]];
  }
  out[0] = sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  sum = ((double )0);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  i = 64;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (i < 494) {
    nzval_t = nzval[i];
    cols_t = cols[i];
    sum += nzval_t * vec[cols_t];
    i++;
  }
  out[1] = sum;
}