Code: #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
#pragma ACCEL PARAM NZVAL_SIZE=auto{4940}
#pragma ACCEL PARAM COLS_SIZE=auto{4940}
#pragma ACCEL PARAM VEC_SIZE=auto{494}
#pragma ACCEL PARAM OUT_SIZE=auto{494}

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double val;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    for (j = cols[i]; j < cols[i + 1]; j++) {
      val = nzval[j];
      sum += val * vec[cols[j]];
    }
    out[i] = sum;
  }
}