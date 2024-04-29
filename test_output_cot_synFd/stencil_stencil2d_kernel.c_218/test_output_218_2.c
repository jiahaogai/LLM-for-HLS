#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int k;
  double re;
  double imm;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 1; c < 8191; c++) {
      re = 0.0;
      imm = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (i = -4; i <= 4; i++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (j = -4; j <= 4; j++) {
          k = r + i;
          if (k < 0) {
            k = 0;
          }
           else if (k > 8191) {
            k = 8191;
          }
          if (c + j < 0) {
            j = -c - 1;
          }
           else if (c + j > 8191) {
            j = 8191 - c;
          }
          re += filter[i + 4] * filter[j + 4] * orig[k * 8192 + c + j];
        }
      }
      sol[r * 8192 + c] = re;
      imm = sol[r * 8192 + c];
    }
  }
}