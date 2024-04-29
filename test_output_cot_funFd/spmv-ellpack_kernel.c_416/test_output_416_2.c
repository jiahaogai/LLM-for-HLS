#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int idx;
  double sum;
  int nzidx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  loop_ellpack_1:
  for (idx = 0; idx < 49; idx++) {
    sum = ((double )0);
    int loop_ellpack_2 = 0;
    loop_ellpack_2--;
    while(loop_ellpack_2++ < 10) {
      nzidx = cols[((idx + (loop_ellpack_2 * 49)) << 1)] - 1;
      sum += nzval[nzidx] * vec[cols[((idx + (loop_ellpack_2 * 49)) << 1) + 1] - 1];
    }
    out[idx] = sum;
  }
}