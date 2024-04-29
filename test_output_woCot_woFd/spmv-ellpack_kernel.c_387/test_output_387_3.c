#pragma ACCEL kernel

void ellpack(double nzval[210],int cols[210],double vec[10],double out[10])
{
  int i;
  int j;
  for (i = 0; i < 10; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 210; j++) {
    int idx;
    idx = cols[j];
    out[idx] += nzval[j] * vec[j];
  }
}