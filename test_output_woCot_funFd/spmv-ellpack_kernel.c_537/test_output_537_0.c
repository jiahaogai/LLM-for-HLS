#pragma ACCEL kernel

void ellpack(double nzval[110],int cols[110],double vec[10],double out[10])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 10; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 110; j++) {
    int idx;
    idx = cols[j];
    out[idx] += nzval[j] * vec[j];
  }
//#pragma endscop
}