Code: #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{494}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_ellpack_0:
/* Standardize from: for(i = 0; i < 494; i++) {*/
  i:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
    loop_ellpack_1:
    for (j = 0; j < 16; j++) {
      sum += nzval[i * 16 + j] * vec[cols[i * 16 + j]];
    }
    out[i] = sum;
  }
}