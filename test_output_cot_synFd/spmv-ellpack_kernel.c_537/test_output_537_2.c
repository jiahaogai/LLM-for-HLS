#pragma ACCEL kernel

void ellpack(double nzval[45],int cols[45],double vec[30],double out[30])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 30; i++) {
    out[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 45; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{8}
    for (i = 0; i < 30; i++) {
      out[cols[j]] += nzval[j] * vec[i];
    }
  }
}