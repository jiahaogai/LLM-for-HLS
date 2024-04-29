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
    
#pragma ACCEL PARALLEL reduction=Si FACTOR=auto{16}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      Si += nzval[j] * vec[cols[j]];
    }
    out[i] = Si;
  }
}