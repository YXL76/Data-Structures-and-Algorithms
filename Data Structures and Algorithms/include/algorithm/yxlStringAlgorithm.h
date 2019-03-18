/**
 * \Author: YXL
 * \LastUpdated: 2018/03/17 18:09:20
 * \description:
 */

#pragma once

#ifndef YXL_STRING_ALGORITHM
#define YXL_STRING_ALGORITHM

class yxlKMP final
{
public:
	yxlKMP();
	template <class T>
	explicit yxlKMP(T& pattern_string);

	void clear();
	template <class T>
	void initialize(T& pattern_string);
	template <typename T>
	int search(T& text_string);

private:
	bool is_initialize_;
	int size_;
	int* next_;
	char* string_;

	template <class T>
	void check_type(T& pattern_string);
};

inline yxlKMP::yxlKMP(): is_initialize_(false), size_(0), next_(nullptr), string_(nullptr)
{
}

inline void yxlKMP::clear()
{
	is_initialize_ = false;
	size_ = 0;
	delete [] next_;
	next_ = nullptr;
	delete [] string_;
	string_ = nullptr;
}

template <typename T>
yxlKMP::yxlKMP(T& pattern_string): is_initialize_(false), size_(0), next_(nullptr), string_(nullptr)
{
	check_type(pattern_string);
	initialize(pattern_string);
	is_initialize_ = true;
}

template <typename T>
void yxlKMP::initialize(T& pattern_string)
{
	check_type(pattern_string);
	if (is_initialize_) { clear(); }
	size_ = pattern_string.size();
	next_ = new int [size_];
	string_ = new char [size_];
	for (auto i = 0; i < size_; ++i) { string_[i] = pattern_string[i]; }
	next_[0] = -1;
	auto left = -1;
	auto right = 0;
	while (right < size_ - 1)
	{
		if (left == -1 || string_[left] == string_[right])
		{
			++left;
			++right;
			if (string_[left] != string_[right]) { next_[right] = left; }
			else { next_[right] = next_[left]; }
		}
		else { left = next_[left]; }
	}
	/*for (auto i = 0 ; i < size_; ++i)
		std::cout << next_[i] << ' ';*/
	is_initialize_ = true;
}

template <typename T>
int yxlKMP::search(T& text_string)
{
	check_type(text_string);

	auto jj = 0;
	auto index_pattern = 0;
	auto index_text = 0;
	const int text_size = text_string.size();
	while (index_text < text_size && index_pattern < size_)
	{
		if (index_pattern == -1 || text_string[index_text] == string_[index_pattern])
		{
			++index_pattern;
			++index_text;
		}
		else { index_pattern = next_[index_pattern]; }
	}
	if (index_pattern == size_) { return index_text - index_pattern; }
	return -1;
}

template <class T>
void yxlKMP::check_type(T& pattern_string)
{
	static_assert(std::is_same<T, std::string>::value || std::is_same<T, yxlArray<char>>::value,
		"the parameter type must be string or yxlArray<char>");
}

#endif // !YXL_STRING_ALGORITHM
