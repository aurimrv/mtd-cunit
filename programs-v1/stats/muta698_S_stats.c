void computeStats(int numbers[], int size)
{
 double med, var, sd, mean, sum, varsum;
 int i;
 sum = 0.0;
 for (i = 0; i < size; i++) {
  sum += numbers[i];
 }
 med = numbers[size / 2];
 mean = sum / size;
 varsum = 0.0;
 for (i = 0; i < size; @
( (var++) ) @
) {
  varsum = varsum + ((numbers[i] - mean) * (numbers[i] - mean));
 }
 var = size <= 1 ? 0 : varsum / (size - 1);
 sd = sqrt(var);
 printf("median:             %2.3f\n", med);
 printf("mean:               %2.3f\n", mean);
 printf("variance:           %2.3f\n", var);
 printf("standard deviation: %2.3f\n", sd);
}