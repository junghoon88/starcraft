#include "singletonBase.h"
#include <time.h>

//====================================
// ## 17.08.07 ## randomFunction ##
//====================================

//                            singletonBase<T>
class randomFunction : public singletonBase<randomFunction>
{
public:

	randomFunction(void)
	{
		srand(GetTickCount());
	}
	~randomFunction(void) {}

	//0 ~ 지정한 숫자 사이에 랜덤한 값을 뽑는다
	inline int getInt(int num) { return rand() % num; }
	//10 ~ 20 이런 식으로 특장 숫자 구간에서 랜덤한 값을 뽑는다.
	inline int getFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

	//실수형 난수
	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }
	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	inline float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}

};