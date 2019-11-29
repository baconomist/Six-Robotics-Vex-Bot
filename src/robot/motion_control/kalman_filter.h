
float kalmanFilter(float estimate, float errorInEstimate, float (*get_measurement)(), float errorInMeasurement,
                   int iterations);
