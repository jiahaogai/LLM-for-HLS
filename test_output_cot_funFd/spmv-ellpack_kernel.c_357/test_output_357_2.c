Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_1(double in[256],double out[32])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
    for (j = 0; j < 256; j++) {
      sum += in[j] * kernel_1_coeff[i * 256 + j];
    }
    out[i] = sum;
  }
}
 #pragma ACCEL kernel

void kernel_2(double in[32],double out[4])
{
  int i;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
    for (int j = 0; j < 32; j++) {
      sum += in[j] * kernel_2_coeff[i * 32 + j];
    }
    out[i] = sum;
  }
}