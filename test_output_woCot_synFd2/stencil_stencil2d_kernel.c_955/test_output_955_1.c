#pragma ACCEL kernel

int t;
int i;
int j;
int k;
int filt;
int orig[8192];
int sol[8192];
int filter[9] = {1,1,1,1,1,1,1,1,1};
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
void kernel_stencil() {
  int t;
  int i;
  int j;
  int k;
  int filt;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 8; t++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 1; i < 33 - 1; i++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 1; j < 33 - 1; j++) {
        for (k = 1; k < 33 - 1; k++) {
          filt = 0;
          for (int r = 0; r < 9; r++) {
            
#pragma ACCEL PARALLEL reduction=filt FACTOR=auto{1}
            for (int s = 0; s < 9; s++) {
              filt += filter[r * 9 + s] * orig[t * 900 + (i + r - 1) * 32 + (j + s - 1) * 32 + k - 1];
            }
          }
          sol[t * 900 + i * 32 + j * 32 + k - 1] = filt;
        }
      }
    }
  }
}