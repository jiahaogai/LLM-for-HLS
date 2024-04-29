Code: #pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
stencil_label1:
   for (i = 0; i < 32; i++) {
      
#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{32}
      stencil_label2:
      for (j = 0; j < 32; j++) {
         tmp = 0.0;
         
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
         stencil_label3:
         for(k = -1; k <= 1; k++) {
             for(l = -1; l <= 1; l++) {
                 tmp += filter[k + 1][l + 1] * orig[i + k][j + l];
             }
         }
         sol[i][j] = tmp;
      }
   }
 }