#pragma once
#include <iostream>
#include <vector>

class DOYOUKNOW_CLASS
{
public:
	DOYOUKNOW_CLASS(void);
	~DOYOUKNOW_CLASS(void);

public:
	void std_vector(void);

	std::vector<int32_t> find_box(	const std::vector<int32_t>& goods,
									const std::vector<int32_t>& boxes,
									const int32_t& goods_idx);

	int32_t find_last_small_box_index(	const std::vector<int32_t>& boxes,
										const std::vector<int32_t>& find_box_index);

	bool input_box(	const std::vector<int32_t>& goods,
					const int32_t& goods_idx,
					const int32_t& last_small_box_index,
					std::vector<int32_t>& save_box);
};
