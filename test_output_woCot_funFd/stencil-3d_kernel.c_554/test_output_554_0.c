#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[250] = {0};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopk:
  for (k = 0; k < 40; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopj:
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 0; i < 40; i++) {
        i_col = i < 39 ? i + 1 : 0;
        j_col = j < 39 ? j + 1 : 0;
        k_col = k < 39 ? k + 1 : 0;
#pragma ACCEL PARALLEL FACTOR=auto{1}
        buf[0] = orig[i + j * 40 + k * 1600];
#pragma ACCEL PARALLEL FACTOR=auto{1}
        buf[25] = orig[i_col + j * 40 + k * 1600];
#pragma ACCEL PARALLEL FACTOR=auto{1}
        buf[50] = orig[i_col + j_col * 40 + k * 1600];
#pragma ACCEL PARALLEL FACTOR=auto{1}
        buf[75] = orig[i_col + j_col * 40 + k_col * 1600];
#pragma ACCEL PARALLEL FACTOR=auto{1}
        buf[100] = orig[i + j_col * 40 + k_col * 1600];
#pragma ACCEL PARALLEL FACTOR=auto{1}
        buf[125] = orig[i + j_col * 40 + k * 1600];
#pragma ACCEL PARALLEL FACTOR=auto{1}
        buf[150] = orig[i + j * 40 + k_col * 1600];
#pragma ACCEL PARALLEL FACTOR=auto{1}
        buf[175] = orig[i_col + j * 40 + k * 1600];
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
        sol[i + j * 40 + k * 1600] = ((buf[0] + buf[25] + buf[50] + buf[75] + buf[100] + buf[125] + buf[150] + buf[175]) / 8 + 1);
      }
    }
  }
}