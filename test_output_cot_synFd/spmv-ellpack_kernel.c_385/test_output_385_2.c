#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 32; j++) {
      val = nzval[i * 32 + j];
      sum += val * vec[cols[i * 32 + j]];
    }
    out[i] = sum;
  }
}