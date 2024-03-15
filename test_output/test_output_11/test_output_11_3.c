
// Xilinx XRT kernel
#pragma ACCEL kernel

void kernel_2mm(double m1[4096],double m2[4096],double m3[4096],double prod[32768])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (j = 0; j < 32; j++) {
      m3[i * 32 + j] = ((double )0);
      for (k = 0; k < 32; k++) {
        m3[i * 32 + j] += m1[i * 32 + k] * m2[k * 32 + j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (j = 0; j < 32; j++) {
      double sum = (double )0;
      for (k = 0; k < 32; k++) {
        sum += m1[i * 32 + k] * m3[k * 32 + j];
      }
      prod[i * 32 + j] = sum;
    }
  }
//#pragma endscop
}
