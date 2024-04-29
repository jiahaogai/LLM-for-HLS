#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_t;
  int cols_t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  sum = ((double )0);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      nzval_t = nzval[i * 16 + j];
      cols_t = cols[i * 16 + j];
      sum += nzval_t * vec[cols_t];
    }
    out[i] = sum;
  }
}