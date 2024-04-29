#pragma ACCEL kernel

 #pragma ACCEL PIPELINE auto{off}

 #pragma ACCEL TILE FACTOR=auto{1}

 #pragma ACCEL PARALLEL FACTOR=auto{1}

int main()
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL reduction = orig FACTOR=auto{16}
    for (j = 0; j < 256; j++) {
      orig[i * 256 + j] = ((i * j) % 256);
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 256 - 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    for (j = 0; j < 256 - 8; j++) {
      int sum = 0;
      
#pragma ACCEL PARALLEL reduction = sum FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[((i + kernel_off[k].i) * 256) + ((j + kernel_off[k].j) * 1)];
      }
      sol[i * 256 + j] = sum;
    }
  }
//#pragma endscop
}