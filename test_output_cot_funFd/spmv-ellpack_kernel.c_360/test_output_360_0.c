#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nzval_tmp;
  int cols_tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  sum = ((double )0);
  for (i = 0; i < 494; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{13}
    for (j = 0; j < 32; j++) {
      nzval_tmp = nzval[i * 32 + j];
      cols_tmp = cols[i * 32 + j];
      sum += nzval_tmp * vec[cols_tmp];
    }
    out[i] = sum;
  }
}