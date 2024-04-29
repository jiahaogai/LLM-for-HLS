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
       
#pragma ACCEL PIPELINE auto{off}
       while (k_col < 9) {
         k = 0 - ((8 - 1) + k_col);
         if (((r + k) >= 0) && ((r + k) < 8)) {
           if ((c + k) >= 0) {
             if ((c + k) < 8) {
               tmp += ((orig[r + k])[c + k]) * filter[k_col];
             }
           }
         }
         k_col++;
       }
       sol[r][c] = tmp;
       c++;
     }
     r++;
   }
}