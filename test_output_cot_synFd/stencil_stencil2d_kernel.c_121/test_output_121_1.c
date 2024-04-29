#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  stencil_label1:
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    stencil_label2:
    for (j = 1; j < 337; j++) {
      s = 0.0;
      stencil_label3:
      for (k = -1; k <= 1; k++) {
        stencil_label4:
        for (idx = -1; idx <= 1; idx++) {
          s += filter[((k + 1) * 3) + idx + 1] * orig[i + k + ((j + idx) * 337)];
        }
      }
      sol[i + (j * 337)] = s;
    }
  }
//#pragma endscop
}