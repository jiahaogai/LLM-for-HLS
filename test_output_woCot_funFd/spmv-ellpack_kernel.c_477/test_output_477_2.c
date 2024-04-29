Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PARAMS auto{vec_len} = 494
Code: #pragma ACCEL PARAMS auto{nzval}
Code: #pragma ACCEL PARAMS auto{cols}
Code: #pragma ACCEL PARAMS auto{vec}
Code: #pragma ACCEL PARAMS auto{out}
 #pragma ACCEL kernel

void spmv_seq(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
}