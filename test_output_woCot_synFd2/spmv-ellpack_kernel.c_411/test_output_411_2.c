#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int index;
  int nz_index;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  loop_ellpack_1:
  for (index = 0; index < 494; index++) {
    sum = ((double )0);
    loop_ellpack_2:
    for (nz_index = cols[index]; nz_index < cols[index + 1]; nz_index++) {
      sum += nzval[nz_index] * vec[((int )nzval[nz_index]) - 1];
    }
    out[index] = sum;
  }
}