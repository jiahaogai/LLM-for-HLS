Code: #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  sum = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 494; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
}