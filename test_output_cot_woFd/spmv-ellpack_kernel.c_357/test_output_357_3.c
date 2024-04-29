#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  loopj:
  for (j = 0; j < 494; j++) {
    sum = ((double )0);
    loopi:
    for (i = 0; i < 16; i++) {
      val = nzval[cols[j * 16 + i]];
      sum += val;
    }
    out[j] = sum;
  }
}