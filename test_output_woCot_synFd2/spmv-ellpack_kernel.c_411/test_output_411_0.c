#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int index;
  int nzidx;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  loop_ellpack_1:
  for (index = 0; index < 494; index++) {
    sum = ((double )0);
    loop_ellpack_2:
    for (nzidx = cols[index]; nzidx < cols[index + 1]; nzidx++) {
      sum += nzval[nzidx] * vec[nzidx];
    }
    out[index] = sum;
  }
}