
 #pragma ACCEL kernel

void kernel_3mm(double m1[4096],double m2[4096],double m3[4096],double prod[32768])
{
  double mult1;
  double mult2;
  double PIPEL_m3[4096];
  double PIPEL_prod[4096];
  double PIPEL_m1[32];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (int i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (int j = 0; j < 64; j++) {
      PIPEL_m1[j] = m1[i + j * 64];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (int k = 0; k < 32; k++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      for (int j = 0; j < 64; j++) {
        PIPEL_m3[j + 64 * k] = m3[i + j * 64] * PIPEL_m1[j];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (int k = 0; k < 32; k++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L6}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
      for (int j = 0; j < 64; j++) {
        mult1 = PIPEL_m1[j + 0] * PIPEL_m2[j + 64 * k];
        mult2 = PIPEL_m1[j + 1] * PIPEL_m2[j + 64 * k + 1];
        for (int i = 0; i < 16; i++) {
          prod[i + 64L * k + 64L * j + 4096L * i] = mult1 + mult2 * ((double )(long )0);
        }
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L7}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
  for (int i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L8}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L8}
    for (int k = 0; k < 32; k++) {
      PIPEL_prod[k] = PIPEL_prod[k] + PIPEL_m3[i + 64L * k];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L9}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
  for (int i = 0; i < 64; i++) {
    for (int k = 0; k < 32; k++) {
      prod[i + 64L * k] = PIPEL_prod[k];
    }
  }
}
