#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    double sum = ((double )0);
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{2}
    for (j = 0; j < 20; j++) {
      int nzidx = i * 20 + j;
      sum += nzval[nzidx] * vec[cols[nzidx]];
    }
    out[i] = sum;
  }
}