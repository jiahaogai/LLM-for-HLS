#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 9; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 8192; k++) {
        int orig_elem;
        int filter_elem;
        int prod;
        
#pragma ACCEL POINTER orig[8192]
        orig_elem = orig[k];
        
#pragma ACCEL POINTER filter[9]
        filter_elem = filter[j] * orig_elem;
        prod = filter_elem;
        sum += prod;
      }
      sol[i] = sum;
    }
  }
}