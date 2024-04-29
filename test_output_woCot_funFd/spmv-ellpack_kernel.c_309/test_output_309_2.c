#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 10; j++) {
    int idx;
    double val;
    val = vec[j];
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{1}
    for (idx = 0; idx < 40; idx++) {
      out[cols[j * 40 + idx]] += nzval[j * 40 + idx] * val;
    }
  }
}