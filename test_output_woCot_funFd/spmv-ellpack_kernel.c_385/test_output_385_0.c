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
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    for (j = cols[i]; j < cols[i + 1]; j++) {
      val = nzval[j];
      sum += val * vec[cols[j]];
    }
    out[i] = sum;
  }
}