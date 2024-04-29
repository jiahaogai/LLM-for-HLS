#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int idx;
  double sum;
  double nzval_idx;
  double vec_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  ellpack_1:
  for (idx = 0; idx < 49; idx++) {
    sum = ((double )0);
    ellpack_2:
    for (; cols[idx + 0] != -1; cols[idx + 0]++) {
      nzval_idx = nzval[cols[idx + 0] + 0];
      vec_idx = vec[cols[idx + 0] + 0];
      sum += nzval_idx * vec_idx;
    }
    out[idx + 0] = sum;
  }
}