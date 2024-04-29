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
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      sol[i * 256 + j] = 0;
      
#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[i * 256 + j] += filter[k] * orig[(i * 256 + j) + ((k - 4) * 256)];
      }
    }
  }
//#pragma endscop
}