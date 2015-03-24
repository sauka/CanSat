#include <iostream>
#include <cmath>

using namespace std;

double p0 = 0.0;
double delta_h = 250.0;
const double v_ref = 5.0;
const double v_neg = 4.02;

double getHeight(double p, double t)
{
    cout << (p / p0) << " " << log(p / p0) << endl;
    return log(p / p0) * t * (-29.24);
}

double convertPressure(int v)
{
    double vout = v_neg + (v * 0.5) / 1023.0;
    return vout / (v_ref * 0.009) + 10.556;
    //double v_pos = v * v_ref / 10230.0 + v_neg;
    //return (v_pos / v_ref - 0.04) / 0.009;
}

int main()
{
//    int start_adc_value;
//    cout << "Enter start adc value: ";
//    cin >> start_adc_value;
//    p0 = convertPressure(start_adc_value);
//    cout << "Start Pressure: " << p0 << endl;
//    while(true) {
//        int adc_value;
//        int t_value;
//        cout << "Enter adc value: ";
//        cin >> adc_value;
//        cout << "Enter t value: ";
//        //cin >> t_value;
//        //double temperature = (t_value >> 4) + (t_value & 0x0F) * 0.0625 + 273.15;
//        double temperature;
//        cin >> temperature;
//        temperature += 273.15;
//        double pressure = convertPressure(adc_value);
//        cout << "Pressure: " << pressure << endl;
//        cout << "Delta height: " << getHeight(pressure, temperature) << endl;
//    }
     cout << "adsfasdf1\r\n";
     cout << "adsfasdf2\r\n";
     cout << "adsfasdf3\r\n";
    return 0;
}
