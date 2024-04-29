#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 0; j < 44; j++) {
    i = 0 + 494 * j;
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{19}
    while (i < 494 + 494 * j) {
      out[cols[i]] += nzval[i] * vec[j];
      i++;
    }
  }
}