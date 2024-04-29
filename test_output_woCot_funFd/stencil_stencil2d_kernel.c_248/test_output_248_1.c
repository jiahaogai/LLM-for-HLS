Code: #pragma ACCEL PIPELINE auto{flatten}
 #pragma ACCEL TILE FACTOR=auto{2}
 #pragma ACCEL PARALLEL FACTOR=auto{4}
#pragma ACCEL PIPELINE auto{off}
 #pragma ACCEL TILE FACTOR=auto{1}
 #pragma ACCEL PARALLEL FACTOR=auto{8}
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{1}
 #pragma ACCEL PARALLEL FACTOR=auto{8}
int main() {
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 32 + 1 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 32 + 1 - 1; j++) {
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sum += filter[k] * orig[i + (-1 + k) * (32 + 1) - 1];
      }
      sol[i * (32 + 1) + j] = sum;
    }
  }
//#pragma endscop
}