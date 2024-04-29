#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long TMP_0;
  long TMP_1;
  long TMP_2;
  long TMP_3;
  long TMP_4;
  long TMP_5;
  long TMP_6;
  long TMP_7;
  long TMP_8;
  long TMP_9;
  long TMP_10;
  long TMP_11;
  long TMP_12;
  long TMP_13;
  long TMP_14;
  long TMP_15;
  long TMP_16;
  long TMP_17;
  long TMP_18;
  long TMP_19;
  long TMP_20;
  long TMP_21;
  long TMP_22;
  long TMP_23;
  long TMP_24;
  long TMP_25;
  long TMP_26;
  long TMP_27;
  long TMP_28;
  long TMP_29;
  long TMP_30;
  long TMP_31;
  long TMP_32;
  long TMP_33;
  long TMP_34;
  long TMP_35;
  long TMP_36;
  long TMP_37;
  long TMP_38;
  long TMP_39;
  long TMP_40;
  long TMP_41;
  long TMP_42;
  long TMP_43;
  long TMP_44;
  long TMP_45;
  long TMP_46;
  long TMP_47;
  long TMP_48;
  long TMP_49;
  long TMP_50;
  long TMP_51;
  long TMP_52;
  long TMP_53;
  long TMP_54;
  long TMP_55;
  long TMP_56;
  long TMP_57;
  long TMP_58;
  long TMP_59;
  long TMP_60;
  long TMP_61;
  long TMP_62;
  long TMP_63;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392; k++) {
      k_col = 392 * k;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1; i < 392; i++) {
        i_col = 392 * i;
        idx = i_col + k_col;
        idx_col = i_col + k;
        TMP_0 = orig[idx_col - 1] + orig[idx_col + 1] + orig[idx - 392] + orig[idx + 392] + C0;
        TMP_1 = orig[idx_col] + C1;
        sol[idx] = TMP_1 + TMP_0;
      }
    }
  }
}