#include <iostream>
#include <fstream>
#include <random>


int main() {

	double x_min = -1.25e+13;
	double x_max = 1.25e+13;
	double v_min = 0;
	double v_max = 0;
	double r_min = 1e+6;
	double r_max = 1e+8;
	double m_min = 1e+29;
	double m_max = 1e+31;
	
	std::uniform_real_distribution<double> unif_x(x_min, x_max);
	std::uniform_real_distribution<double> unif_v(v_min, v_max);
	std::uniform_real_distribution<double> unif_r(r_min, r_max);
	std::uniform_real_distribution<double> unif_m(m_min, m_max);
	std::default_random_engine re;

	std::ofstream out("100_particles.txt");
	out << "100_particles\n1.25e+13 1.25e+13 1.25e+13\n315360000\n100\n86400\n100\n";
	for (int i = 0; i < 100; ++i) {
		out << "P" << (i + 1) << " " << unif_m(re) << " " << unif_r(re) << " " << unif_x(re) / 10. << " " << unif_x(re) / 10. << " 0 " << unif_v(re) << " " << unif_v(re) << " 0\n";
	}
	out.close();
	return 0;
}