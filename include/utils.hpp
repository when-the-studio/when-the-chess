#ifndef HEADER_WHEN_THE_CHESS_UTILS_
#define HEADER_WHEN_THE_CHESS_UTILS_

template<typename T>
inline T max(T a, T b) {
	return a < b ? b : a;
}

template<typename T>
inline T min(T a, T b) {
	return a < b ? a : b;
}

#endif /* HEADER_WHEN_THE_CHESS_UTILS_ */
