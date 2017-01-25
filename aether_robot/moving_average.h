/**
moving_average.h
Helper class that maintains a moving average over a set of samples.
Adapted from author: Miguel Grinberg (Michelino robot)
http://bit.ly/2kkeHwu
*/

/*
 * Template class enables moving averages to be computed on samples of different types.
 * args: V is class type
 *       N is how many samples need to be kept in memory to take average
 */
template <typename V, int N> class MovingAverage
{
  public:
  /* 
   *  Class constructor
   *  def is default value to initialise average.
   */
  MovingAverage(V def = 0) : sum(0), p(0)
  {
    for (int i = 0; i < N; i++) {
      samples[i] = def;
      sum += samples[i];
    }
  }

  /*
   * Add a new sample
   * new_sample is the new sample to add to the moving average.
   * return the updated average.
   */
  V add(V new_sample)
  {
    sum = sum - samples[p] + new_sample;
    samples[p++] = new_sample; // pointer moves to next entry
    if (p >= N)
      p = 0;
    return sum / N;
  }

  private:
  V samples[N];
  V sum;        // keeps sum of N samples in memeory
  V p;          // pointer indicates entry in circular buffer where next sample will be stored.
  
};

