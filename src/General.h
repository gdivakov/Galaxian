#pragma once

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

template<typename T1, typename T2>
void removeFromArray(std::vector<T1*>& arr, T2* p)
{
	auto removeIter = remove(arr.begin(), arr.end(), p);
	arr.erase(removeIter, arr.end());
}