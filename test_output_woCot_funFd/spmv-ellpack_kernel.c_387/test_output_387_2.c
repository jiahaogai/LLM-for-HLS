#pragma ACCEL kernel

void ellpack(double nzval[192],int cols[192],double vec[24],double out[12])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 12; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 192; j++) {
    out[cols[j]] += nzval[j] * vec[j / 8];
  }
//#pragma endscop
}