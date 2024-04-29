#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double Si;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  int idx = 0;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  while (idx < 494) {
    Si = ((double )0);
    int jj = idx;
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    while (jj < 494 + idx) {
      i = jj % 494;
      j = jj / 494;
      Si += nzval[jj] * vec[cols[i]];
      jj++;
    }
    out[i] = Si;
    idx += 16;
  }
}