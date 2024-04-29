Code: #pragma ACCEL kernel

int main()
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 32; j++) {
      sol[i * 32 + j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        sol[i * 32 + j] += filter[k] * orig[i * 32 + j * 9 + k];
      }
    }
  }
//#pragma endscop
}