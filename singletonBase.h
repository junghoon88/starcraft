#pragma once

template <typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase(void) {};
	~singletonBase(void) {};

public:
	//ΩÃ±€≈Ê ¡¢±Ÿ¿⁄
	static T* getSingleton(void);
	//ΩÃ±€≈Ê ∏±∏Æ¡Ó
	void releaseSingleton(void);

};

//ΩÃ±€≈Ê √ ±‚»≠
template<typename T>
T* singletonBase<T>::singleton = 0;

//¡¢±Ÿ¿⁄
template <typename T>
T* singletonBase<T>::getSingleton(void)
{
	//ΩÃ±€≈Ê¿Ã æ¯¥Ÿ∏È «“¥Á«ÿ∂Û
	if (!singleton) singleton = new T;

	return singleton;
}

template <typename T>
void singletonBase<T>::releaseSingleton(void)
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}