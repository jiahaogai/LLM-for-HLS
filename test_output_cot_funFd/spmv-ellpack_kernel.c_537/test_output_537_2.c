#pragma ACCEL kernel

void ellpack(double nzval[4096],int cols[4096],double vec[64],double out[64])
{
  int i;
  int j;
  for (i = 0; i < 64; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 64; j++) {
    int k;
    double sum;
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 16; k++) {
      sum += nzval[cols[j * 16 + k]] * vec[k];
    }
    out[j] = sum;
  }
}