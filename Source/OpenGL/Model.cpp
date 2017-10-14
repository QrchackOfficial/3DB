#include "Model.hpp"

Model::Model() {
	for (int v = 0; v < 12 * 3; v++) {
		mColorData[3 * v + 0] = getRandom();
		mColorData[3 * v + 1] = getRandom();
		mColorData[3 * v + 2] = getRandom();
	}
}
