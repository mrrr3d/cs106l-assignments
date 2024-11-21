/*
 * CS106L Assignment 4: Weather Forecast
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 */

#include <algorithm>
#include <random>
#include <vector>
#include <iostream>


/* #### Please feel free to use these values, but don't change them! #### */
double kMaxTempRequirement = 5;
double uAvgTempRequirement = 60;

struct Forecast {
  double min_temp;
  double max_temp;
  double avg_temp;
};

Forecast compute_forecast(const std::vector<double>& dailyWeather) {
  // STUDENT TODO 1: return a forecast for the daily weather that is passed in.
  auto min = std::min_element(dailyWeather.begin(), dailyWeather.end());
  auto max = std::max_element(dailyWeather.begin(), dailyWeather.end());
  auto avg = std::accumulate(dailyWeather.begin(), dailyWeather.end(), 0.0);
  return {*min, *max, avg / dailyWeather.size()};
}

std::vector<Forecast> get_forecasts(const std::vector<std::vector<double>>& weatherData) {
  /*
   * STUDENT TODO 2: returns a vector of Forecast structs for the weatherData which contains
   * std::vector<double> which contain values for the weather on that day.
   */
  // 最开始初始化res没设置大小, 调试发现 __result=non-dereferenceable iterator for std::vector
  std::vector<Forecast> res(weatherData.size());
  std::transform(weatherData.begin(), weatherData.end(), res.begin(), compute_forecast);
  return res;
}

std::vector<Forecast> get_filtered_data(const std::vector<Forecast>& forecastData) {
  // STUDENT TODO 3: return a vector with Forecasts filtered for days with specific weather.
  auto rmN = [](Forecast x) {
    return x.avg_temp < uAvgTempRequirement ||
          x.max_temp - x.min_temp <= kMaxTempRequirement;
  };
  std::vector<Forecast> res(forecastData);

  res.erase(std::remove_if(res.begin(), res.end(), rmN), res.end());
  return res;
}


std::vector<Forecast> get_shuffled_data(const std::vector<Forecast>& forecastData) {
  // STUDENT TODO 4: Make use of a standard library algorithm to shuffle the data!
  std::random_device rd;
  std::mt19937 g(rd());
  std::vector<Forecast> res(forecastData);

  std::shuffle(res.begin(), res.end(), g);
  return res;
}

std::vector<Forecast> run_weather_pipeline(const std::vector<std::vector<double>>& weatherData) {
  // STUDENT TODO 5: Put your functions together to run the weather pipeline!
  auto d1 = get_forecasts(weatherData);
  d1 = get_filtered_data(d1);
  d1 = get_shuffled_data(d1);
  return d1;  
}

/* #### Please don't change this line! #### */
#include "utils.cpp"