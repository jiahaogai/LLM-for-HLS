### Code:
 #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  ellpack_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    ellpack_2:
    for (j = 0; j < 10; j++) {
      val = nzval[i * 10 + j];
      sum += val * vec[cols[i * 10 + j]];
    }
    out[i] = sum;
  }
}