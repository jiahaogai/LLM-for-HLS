Code: #pragma ACCEL kernel
   | ^


#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    for (j = cols[i]; j < cols[i + 1]; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
}