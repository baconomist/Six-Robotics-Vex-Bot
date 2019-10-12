#include <iostream>

using namespace std;

/**
* @returns 1 >= gain >= 0
* When the kalman gain is small, the error in measurement is larger and vice-versa
* **/
float calculateKalmanGain(float errorInEstimate, float errorInData)
{
  float gain = errorInEstimate / (errorInEstimate + errorInData);
  return gain;
}

// Watch ep3
float calculateKalmanEstimate(float gain, float previousEstimate, float measuredValue)
{
  // as algorithm runs, gain decreases, less weight is put on the measured value
  // and our estimates become more accurate and closer to the true value
  float est = previousEstimate + gain * (measuredValue - previousEstimate);
  return est;
}

float calculateNewErrorInEstimate(float errorInMeasurement, float previousErrorInEstimate, float kalmanGain,
  float kalmanEstimate)
  {
    // The same thing as eEst = (1 - gain)(previous error in estimate)
    float eEst = (errorInMeasurement * previousErrorInEstimate) / (errorInMeasurement + previousErrorInEstimate);

    return eEst;
  }


  float kalmanFilter(float estimate, float errorInEstimate, float (*get_measurement)(), float errorInMeasurement, int iterations)
  {
    if(iterations <= 0)
    return estimate;

    float gain = calculateKalmanGain(errorInEstimate, errorInMeasurement);
    float current_estimate = calculateKalmanEstimate(gain, estimate, get_measurement());

    float current_error_in_estimate = calculateNewErrorInEstimate(errorInMeasurement, errorInEstimate, gain, current_estimate);

    iterations--;
    return kalmanFilter(current_estimate, current_error_in_estimate, get_measurement, errorInMeasurement, iterations);
  }
