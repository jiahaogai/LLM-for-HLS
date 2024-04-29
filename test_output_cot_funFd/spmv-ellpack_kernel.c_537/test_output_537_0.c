#pragma ACCEL kernel

void ellpack(double nzval[15],int cols[12],double vec[4],double out[4])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 4; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 12; j++) {
    for (i = 0; i < 4; i++) {
      out[cols[j]] += nzval[j * 4 + i] * vec[i];
    }
  }
//#pragma endscop
}