#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double Si;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  spmv_1:
  for (i = 0; i < 494; i++) {
    Si = 0.0;
    spmv_2:
    for (j = 0; j < 32; j++) {
      Si += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
    }
    out[i] = Si;
  }
}