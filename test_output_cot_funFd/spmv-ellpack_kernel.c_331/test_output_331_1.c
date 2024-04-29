#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
  double sum;
  for (i = 0; i < 49; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (i = 0; i < 49; i++) {
    sum = 0.0;
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[j];
    }
    out[i] = sum;
  }
}