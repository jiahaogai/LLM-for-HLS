#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double Si;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    Si = 0.0;
    int jj = cols[i];
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (jj < cols[i + 1]) {
      Si += nzval[jj] * vec[cols[jj]];
      jj++;
    }
    out[i] = Si;
  }
}