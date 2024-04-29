#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int r;
  int c;
  int k1;
  int k2;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  r = 0;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  while (r < 8) {
     c = 0;    
     while (c < 8) {
       tmp = 0;       
       k_col = 0;      
       while (k_col < 9) {
         k = k_col + (8 * r);       
         tmp += filter[k_col] * orig[k];       
         k_col++;      }      
       sol[r * 8 + c] = tmp;      
       c++;     }    
     r++;  }  
}