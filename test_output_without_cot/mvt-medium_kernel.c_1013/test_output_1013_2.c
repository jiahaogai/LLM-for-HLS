c
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
  }
  for (i = 0; i < 400; i++) {
    y_1[i] = y_1[i] * x1[i];
  }
  for (i = 0; i < 400; i++) {
    x2[i] = ((double )0);
  }
  for (i = 0; i < 400; i++) {
    y_2[i] = y_2[i] * x2[i];
  }
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
  }
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      x2[i] += A[j][i] * y_2[j];
    }
  }
}