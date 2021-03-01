#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

#include "constant.h"

const int LayersNumD = 2;
const int LayersNumG = 2;

struct Discriminator {
	int Onum = 0;
	int Wnum = 0;
	int Dnum = 0;
	int Layer[LayersNumD] = { 784, 1 };
};
struct Generator {
	int Onum = 0;
	int Wnum = 0;
	int Dnum = 0;
	int Layer[LayersNumD] = { 20, 784 };
};

static Discriminator discriminator;
static Generator generator;

int main() {

	for (int i = 0; i < LayersNumD; i++) {
		discriminator.Onum = discriminator.Onum + discriminator.Layer[i];
	}
	for (int i = 0; i < (LayersNumD - 1); i++) {
		discriminator.Wnum = discriminator.Wnum + discriminator.Layer[i] * discriminator.Layer[i + 1];
	}

	for (int i = 0; i < LayersNumG; i++) {
		generator.Onum = generator.Onum + generator.Layer[i];
	}
	for (int i = 0; i < (LayersNumG - 1); i++) {
		generator.Wnum = generator.Wnum + generator.Layer[i] * generator.Layer[i + 1];
	}

	std::vector<float> out(discriminator.Onum, 0);
	std::vector<float> outOld(discriminator.Onum, 0);
	std::vector<float> weight(discriminator.Wnum);
	std::vector<float>del(discriminator.Onum, 0);
	std::vector<float>delOld(discriminator.Onum, 0);

	std::vector<float> Gout(generator.Onum, 0);
	std::vector<float> GoutOld(generator.Onum, 0);
	std::vector<float> Gweight(generator.Wnum);

	Random(weight, -1, 1, 0, discriminator.Wnum, clock());
	Random(Gweight, -1, 1, 0, generator.Wnum, clock());

	for (int epoch = 0; epoch < 10000; epoch++) {
		cv::Mat image = cv::imread("F:\\Foton\\ngnl_data\\training\\help\\" + std::to_string(rand() % 10) + "\\" + std::to_string(epoch % 5000) + ".png", CV_8UC1);
		Image(image, out, 0);

		for (int i = 0; i < (LayersNumD - 1); i++) {
			SumFunc(out, weight, discriminator.Layer, i);
		}

		outOld = out;
		float out1 = out[discriminator.Onum - discriminator.Layer[LayersNumD - 1]];

    /*----------------------------------------------------------------------------*/
		Random(Gout, 0, 1, 0, generator.Layer[0], clock());
		for (int i = 0; i < (LayersNumG - 1); i++) {
			SumFunc(Gout, Gweight, generator.Layer, i);
		}
		for (int i = 0; i < generator.Layer[LayersNumG - 1]; i++) {
			out[i] = Gout[generator.Onum - generator.Layer[LayersNumG - 1] + i];
		}
    /*----------------------------------------------------------------------------*/                             //загрузка любых данных, формат в vector<float>[in.size^2]
		Out(out, 0);


		for (int i = 0; i < (LayersNumD - 1); i++) {
			SumFunc(out, weight, discriminator.Layer, i);
		}
		float out2 = out[discriminator.Onum - discriminator.Layer[LayersNumD - 1]];


		float LossFucntionD = log(out1) + log(1 - out2);
		float LossFucntionG = log(out2);
		//float LossFunctionD = ()

		std::cout.precision(3);
		std::cout << out1 << "   " << out2 << "   " << "LossD: " <<  LossFucntionD << "    LossG: " << LossFucntionG << std::endl;


		for (int i = 0; i < discriminator.Layer[LayersNumD - 1]; i++) {
			for (int j = 0; j < discriminator.Layer[LayersNumD - 2]; j++) {
				int OutNum = discriminator.Onum - discriminator.Layer[LayersNumD - 1] - discriminator.Layer[LayersNumD - 2];
				int WeightNum = discriminator.Wnum - discriminator.Layer[LayersNumD - 1] * discriminator.Layer[LayersNumD - 2] + i * discriminator.Layer[LayersNumD - 2] + j;


				delOld[j] = (1 - out1) * outOld[OutNum + j];
				del[j] = out2 * out[OutNum + j];
				weight[WeightNum] = weight[WeightNum] + Step * (delOld[j] - del[j]);
			}
		}

		for (int i = 0; i < (LayersNumD - 2); i++) {
			Iter(out, outOld, weight, del, delOld, discriminator.Layer, i, LayersNumD);
		}
	}
}
