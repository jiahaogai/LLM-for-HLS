#pragma ACCEL kernel

void ellpack(double nzval[153],int cols[115],double vec[101],double out[101])
{
  int i;
  int j;
  for (i = 0; i < 101; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 115; j++) {
    int idx;
    idx = cols[j];
    out[idx] += nzval[j] * vec[j];
  }
}