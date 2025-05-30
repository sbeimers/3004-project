#ifndef CONSTS_H
#define CONSTS_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<float> LOW_COHERENCE_PLOT_POINTS {61,65,62,66,59,63,66,64,69,62,65,68,71,74,76,80,76,73,78,76,82,85,88,90,92,88,84,86,82,87,82,83,79,74,77,72,73,70,74,77,73,73,69,65,69,67,70,73,70,67,69,71,67,65,68,71,67,70,74,71,69,66,70,72,74,75,77,80,82,80,79,82,76,74,78,75,79,81,84,78,80,75,72,76,70,67,69,71,73,76,78,80,82,85,76,79,79,81,83,78,81,80,82,85,81,83,79,76,80,78,75,74,72,70,68,67,70,61,63,65,58,57,60,63,65,62,59,60,63,66,61,59,57,59,60,63,58,55,52,56,58,61,63,59,64,67,64,67,71,67,64,73,69,75,78,73,76,79,78,81,85,79,81,83,79,74,76,80,74,71,74,77,71,67,73,70,73,76,74,71,64,69,58,66,62,63,66,64,69,71,75,79,68,65,72,62,68,69,72,67};
vector<float> MED_COHERENCE_PLOT_POINTS { 70,71,74,76,77,78,77,73,71,75,70,69,67,64,66,63,60,58,56,57,58,60,62,65,66,68,70,72,74,75,77,78,78,79,79,78,76,75,74,72,70,69,66,65,63,64,65,68,69,70,73,75,75,76,77,79,78,76,74,75,72,70,67,66,65,63,62,61,63,65,67,70,74,72,76,78,80,82,84,81,79,77,75,72,71,67,70,65,63,61,62,64,67,69,71,72,74,75,77,78,78,76,73,72,69,71,67,64,63,61,62,64,67,69,71,72,74,77,79,80,81,77,79,75,73,71,69,67,64,62,61,62,64,65,68,71,73,76,78,78,81,81,81,80,78,77,75,72,74,70,68,65,63,62,60,60,64,62,66,68,69,71,72,73,74,75,77,78,77,75,72,70,69,67,65,62,62,64,65,67,69,70,72,75,75,75,73,70,68,66,64,63,62,61,60,61,63,65,68,69};
vector<float> HIGH_COHERENCE_PLOT_POINTS { 69.1, 67.2, 64.6, 61.4, 58.1, 55.0, 52.4, 50.7, 50.0, 50.4, 51.9, 54.2, 57.2, 60.5, 63.7, 66.6, 68.7, 69.8, 69.9, 68.9, 66.9, 64.1, 60.9, 57.6, 54.6, 52.1, 50.5, 50.0, 50.6, 52.2, 54.6, 57.7, 61.0, 64.2, 66.9, 68.9, 69.9, 69.8, 68.6, 66.5, 63.7, 60.4, 57.1, 54.1, 51.8, 50.4, 50.0, 50.7, 52.5, 55.1, 58.2, 61.5, 64.7, 67.3, 69.1, 70.0, 69.7, 68.4, 66.1, 63.2, 59.9, 56.6, 53.7, 51.5, 50.3, 50.1, 50.9, 52.8, 55.5, 58.7, 62.0, 65.1, 67.6, 69.3, 70.0, 69.6, 68.1, 65.7, 62.7, 59.4, 56.2, 53.4, 51.3, 50.2, 50.1, 51.2, 53.2, 56.0, 59.2, 62.5, 65.5, 67.9, 69.5, 70.0, 69.4, 67.8, 65.3, 62.2, 58.9, 55.7, 53.0, 51.0, 50.1, 50.2, 51.4, 53.6, 56.4, 59.7, 63.0, 65.9, 68.2, 69.6, 70.0, 69.2, 67.5, 64.9, 61.7, 58.4, 55.3, 52.6, 50.8, 50.0, 50.3, 51.7, 54.0, 56.9, 60.2, 63.4, 66.3, 68.5, 69.8, 69.9, 69.0, 67.1, 64.4, 61.2, 57.9, 54.8, 52.3, 50.6, 50.0, 50.5, 52.0, 54.4, 57.4, 60.7, 63.9, 66.7, 68.8, 69.9, 69.9, 68.8, 66.7, 64.0, 60.7, 57.4, 54.4, 52.0, 50.5, 50.0, 50.6, 52.3, 54.8, 57.9, 61.2, 64.4, 67.1, 69.0, 69.9, 69.8, 68.5, 66.4, 63.5, 60.2, 57.0, 54.0, 51.7, 50.3, 50.0, 50.8, 52.6, 55.2, 58.4, 61.7, 64.8, 67.4, 69.2, 70.0, 69.7, 68.3, 66.0, 63.0, 59.7, 56.5, 53.6, 55.2, 58.4, 61.7, 64.8, 67.4 };

vector<float> LOW_COHERENCE_SCORES { 0.4, 0.5, 0.6, 0.4, 0.6, 0.6, 0.7, 0.8, 0.2, 0.9, 0.8, 0.4, 0.0, 0.9, 0.1, 0.1, 0.9, 1.0, 0.1, 1.0, 0.5, 0.5, 0.5, 0.9, 0.3, 0.9, 0.9, 0.3, 0.2, 0.4, 0.5, 0.8, 0.5, 0.2, 0.5, 0.1, 0.9, 0.7, 0.0, 0.9 };
vector<float> MED_COHERENCE_SCORES { 2.9, 3.1, 4.0, 3.1, 2.2, 3.4, 2.9, 2.2, 2.3, 3.2, 3.9, 2.0, 3.2, 3.3, 3.4, 2.2, 4.0, 3.3, 3.4, 3.6, 2.4, 2.1, 3.2, 3.5, 2.0, 3.0, 3.9, 3.1, 2.3, 3.4, 2.6, 2.4, 3.7, 2.8, 3.5, 2.5, 2.9, 3.1, 2.7, 2.6 };
vector<float> HIGH_COHERENCE_SCORES { 6.4, 8.5, 5.2, 6.6, 8.7, 8.2, 5.9, 7.7, 6.7, 8.5, 6.0, 7.1, 6.6, 7.6, 8.4, 7.8, 8.5, 7.1, 8.4, 9.0, 7.2, 6.1, 7.7, 7.1, 6.9, 6.5, 5.9, 7.8, 8.5, 6.2, 8.3, 8.9, 8.8, 5.7, 7.1, 7.7, 8.6, 8.2, 8.2, 6.7 };

#endif // CONSTS_H
