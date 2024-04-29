#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int index;
  int nnz;
  double sum;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  loop_ellpack_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    nnz = cols[i];
    index = nzval[i];
    loop_ellpack_2:
    for (j = 1; j < nnz; j++) {
      sum += nzval[index + j] * vec[cols[index + j]];
    }
    out[i] = sum;
  }
}