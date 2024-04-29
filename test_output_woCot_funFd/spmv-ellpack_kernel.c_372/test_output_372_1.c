#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[4940],double out[4940])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 4940; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      out[i] += nzval[cols[i] + j * 1240] * vec[cols[i] + j * 1240];
    }
  }
}