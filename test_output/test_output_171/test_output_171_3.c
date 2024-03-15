
\\begin{equation}
\begin{aligned}
  & f\left( x, y \right) = \sum_{i=1}
\end{aligned}
\end{equation}
	for(i = 1; i < 120; i++) {
	  tmp = 0.0;
	  float tmp_stddev = 0.0;
	  for(j = 1; j < 120; j++) {
	    tmp += A[i][j] * B[i][j];
	  }
	  
#pragma ACCEL PIPELINE auto{off}
	  
#pragma ACCEL TILE FACTOR=auto{2}
	  for(j = 1; j < 120; j++) {
	    tmp_stddev += (A[i][j] - tmp) * (A[i][j] - tmp);
	  }
	  tmp_stddev = sqrt(tmp_stddev / 119.0);
	  Q[i] = tmp / tmp_stddev;
	}
}
