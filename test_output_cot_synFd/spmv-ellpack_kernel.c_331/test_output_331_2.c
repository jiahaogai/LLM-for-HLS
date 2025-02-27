#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
  double sum;
  double nz_val;
  double col;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (i = 0; i < 49; i++) {
    sum = ((double )0);
    for (j = 0; j < 494; j++) {
      nz_val = nzval[i * 494 + j];
      col = cols[i * 494 + j];
      sum += nz_val * vec[col];
    }
    out[i] = sum;
  }
}