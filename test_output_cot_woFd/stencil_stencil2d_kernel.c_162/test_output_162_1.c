#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[256])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    buf = orig[i];
    middle:
    for (j = 0; j < 256; j++) {
      k_col = i - 128 + j;
      if (k_col < 0) {
        k_col += 8192;
      }
      else {
        if (k_col > 8191) {
          k_col -= 8192;
        }
      }
      k = filter[j];
      sol[i] += buf * k * orig[k_col];
    }
  }
}