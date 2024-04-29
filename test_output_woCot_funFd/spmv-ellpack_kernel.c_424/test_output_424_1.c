#pragma ACCEL kernel

void ellpack(double nzval[200],int cols[200],double vec[25],double out[100])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 100; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
}