<<<<<<< HEAD
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
<<<<<<< HEAD
  outer:
  for (i = 0; i < 8192; i++) {
=======
  for (i = 1; i < 32 + 1 - 1; i++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
<<<<<<< HEAD
    middle:
    for (j = 0; j < 8; j++) {
      idx = i * 8 + j;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        val += orig[idx * 9 + k] * filter[k];
      }
      sol[idx] = val;
    }
  }
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}