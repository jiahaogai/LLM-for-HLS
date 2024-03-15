
 #pragma ACCEL kernel

void kernel_gemm(double m1[4096],double m2[4096],double prod[4096])
{
  double temp_1[32768];
  double temp_2[32768];
  double mul[1024];
  int i;
  int j;
  int k;
  int k_col;
  int temp_1_idx;
  int temp_2_idx;
  int mul_idx;
  int mul_col;
  
#pragma ACCEL PIPELINE auto{flatten}
  loopj:
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    loopi:
    for (i = 0; i < 64; i++) {
      temp_1_idx = (((64) * i) + j);
      double sum = m1[temp_1_idx] * 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L5}
      loopk:
      for (k = 0; k < 64; k++) {
        k_col = (((64) * k) + j);
        mul_idx = (64 * k) + i;
        sum += m1[k_col] * m2[mul_idx];
      }
      temp_2_idx = (((64) * i) + j);
      mul[temp_2_idx] = sum;
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L0}
  loopk_col:
  for (k_col = 0; k_col < 64; k_col++) {
    
#pragma ACCEL PARALLEL reduction=prod FACTOR=auto{__PARA__L6}
    loopi:
    for (i = 0; i < 64; i++) {
      mul_idx = (64 * i) + k_col;
      prod[mul_idx] = mul[mul_idx] * 0;
    }
    int _in_prod = prod[k_col];
    prod[k_col] = _in_prod;
  }
}
