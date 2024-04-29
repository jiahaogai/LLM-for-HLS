#pragma ACCEL kernel

void ellpack(double nzval[16],int cols[8],double vec[4],double out[4])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 4; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 8; j++) {
    for (i = 0; i < 4; i++) {
      out[cols[j]] += nzval[j * 4 + i] * vec[i];
    }
  }
//#pragma endscop
}