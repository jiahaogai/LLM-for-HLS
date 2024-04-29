Regards,
The ACCEL Team


__ACCEL__

#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  int si;
  double sum;
  double Si;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  ellpack_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    ellpack_2:
    for (j = 0; j < 10; j++) {
      si = j + i * 10;
      Si = nzval[si] * vec[cols[si]];
      sum += Si;
    }
    out[i] = sum;
  }
}