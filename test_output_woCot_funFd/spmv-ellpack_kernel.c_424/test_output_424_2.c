#pragma ACCEL kernel

void ellpack(double nzval[128],int cols[128],double vec[16],double out[16])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 16; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 128; j++) {
    int idx;
    idx = cols[j];
    out[idx] += nzval[j] * vec[j];
  }
//#pragma endscop
}