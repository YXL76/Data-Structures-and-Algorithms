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
	auto prefix = -1;
	auto suffix = 0;
	while (suffix < size_ - 1)
	{
		if (prefix == -1 || string_[suffix] == string_[prefix])
		{
			++suffix;
			++prefix;
			if (string_[suffix] != string_[prefix]) { next_[suffix] = prefix; }
			else { next_[suffix] = next_[prefix]; }
		}
		else { prefix = next_[prefix]; }
	}
	is_initialize_ = true;
}

template <typename T>
int yxlKMP::search(T& text_string)
{
	check_type(text_string);
	auto index_pattern = 0;
	auto index_text = 0;
	const int text_size = text_string.size();
	while (index_pattern < text_size && index_text < size_)
	{
		if (index_text == -1 || text_string[index_pattern] == string_[index_text])
		{
			++index_pattern;
			++index_text;
		}
		else { index_text = next_[index_text]; }
	}
	if (index_text == size_) { return index_pattern - index_text; }
	return -1;
}

template <class T>
void yxlKMP::check_type(T& pattern_string)
{
	static_assert(std::is_same<T, std::string>::value || std::is_same<T, yxlArray<char>>::value,
		"the parameter type must be string or yxlArray<char>");
}

#endif // !YXL_STRING_ALGORITHM