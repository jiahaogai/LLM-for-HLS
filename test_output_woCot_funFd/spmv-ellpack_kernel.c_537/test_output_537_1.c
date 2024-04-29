#pragma ACCEL kernel

void ellpack(double nzval[192],int cols[192],double vec[16],double out[16])
{
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 16; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      out[i] += nzval[cols[i + j * 16] - 1] * vec[j];
    }
  }
//#pragma endscop
}