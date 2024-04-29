#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 64; j++) {
    double temp_1;
    int k;
    double sum;
    sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (k = 0; k < 64; k++) {
      double nzval_tmp;
      int cols_tmp;
      nzval_tmp = nzval[((j * 64) + k)];
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      cols_tmp = cols[((j * 64) + k)];
      sum += nzval_tmp * vec[cols_tmp];
    }
    temp_1 = sum + out[j];
    out[j] = temp_1;
  }
}