#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>

// 生成带有多个正弦波的信号
std::vector<double> generateSignal(int N, double fs, const std::vector<double>& freqs) {
    std::vector<double> signal(N, 0.0);
    for (size_t i = 0; i < freqs.size(); ++i) {
        for (int n = 0; n < N; ++n) {
            signal[n] += std::sin(2 * M_PI * freqs[i] * n / fs);
        }
    }
    return signal;
}

// 简单的DFT实现
void DFT(const std::vector<double>& signal, std::vector<double>& mag, double fs) {
    int N = signal.size();
    mag.resize(N / 2);
    for (int k = 0; k < N / 2; ++k) {
        double real = 0.0, imag = 0.0;
        for (int n = 0; n < N; ++n) {
            double angle = 2 * M_PI * k * n / N;
            real += signal[n] * std::cos(angle);
            imag -= signal[n] * std::sin(angle);
        }
        mag[k] = std::sqrt(real * real + imag * imag) / N;
    }
}

int main() {
    int N = 10240;         // 采样点数
    double fs = 10240.0;   // 采样频率
    std::vector<double> freqs = {50.0, 120.0, 300.0, 1000, 1200, 4500}; // 信号中包含的正弦波频率

    // 生成信号
    std::vector<double> signal = generateSignal(N, fs, freqs);

    // 计算DFT
    std::vector<double> mag;
    DFT(signal, mag, fs);

    // 输出主要频率分量
    std::cout << "Detected frequencies (Hz):" << std::endl;
    for (int k = 0; k < mag.size(); ++k) {
        if (mag[k] > 0.3) { // 阈值可调整
            double freq = k * fs / N;
            std::cout << freq << " Hz, Magnitude: " << mag[k] << std::endl;
        }
    }
    return 0;
}