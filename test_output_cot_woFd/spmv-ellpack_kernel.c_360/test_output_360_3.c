#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    val = ((double )0);
    ints:
    for (j = 0; j < 5; j++) {
      val = nzval[i * 5 + j];
      sum = sum + val * vec[cols[i * 5 + j]];
    }
    out[i] = sum;
  }
}