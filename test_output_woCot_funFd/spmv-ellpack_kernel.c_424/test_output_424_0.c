#pragma ACCEL kernel

void ellpack(double nzval[16],int cols[8],double vec[4],double out[4])
{
  int i;
  int j;
//#pragma scop
  for (i = 0; i < 4; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[j - cols[i]];
    }
  }
//#pragma endscop
}