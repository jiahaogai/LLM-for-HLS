#pragma ACCEL kernel

void ellpack(double nzval[16],int cols[16],double vec[4],double out[1])
{
  int i;
  int j;
  double sum;
  sum = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 4; i++) {
    sum = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 16; j++) {
      sum += nzval[j] * vec[cols[j]];
    }
    out[i] = sum;
  }
}