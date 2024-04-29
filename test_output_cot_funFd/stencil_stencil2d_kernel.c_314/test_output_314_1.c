#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8186; j++) {
      buf[0] = orig[index(i - 1,j - 1)];
      buf[1] = orig[index(i - 1,j)];
      buf[2] = orig[index(i - 1,j + 1)];
      buf[3] = orig[index(i,j - 1)];
      buf[4] = orig[index(i,j)];
      buf[5] = orig[index(i,j + 1)];
      buf[6] = orig[index(i + 1,j - 1)];
      buf[7] = orig[index(i + 1,j)];
      buf[8] = orig[index(i + 1,j + 1)];
      sol[index(i,j)] = filter(buf);
    }
  }
}