#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 494; j++) {
    int k;
    double sum;
    sum = 0.0;
    for (k = 0; k < 32; k++) {
      sum += nzval[i * 32 + k] * vec[cols[i * 32 + k]];
    }
    out[j] += sum;
  }
}