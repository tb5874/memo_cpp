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

		void find_box(	const std::vector<int32_t>& goods,
						const int32_t& goods_idx,
						const std::vector<int32_t>& boxes,
						std::vector<int32_t>& find_box_idx);

		void find_last_small_box_index(	const std::vector<int32_t>& boxes,
										const std::vector<int32_t>& find_box_idx,
										int32_t& small_box_idx);

		void input_box(	const std::vector<int32_t>& goods,
						const int32_t& goods_idx,
						const int32_t& small_box_idx,
						std::vector<int32_t>& box_and_goods,
						bool& input_result);

		void find_next_box(	std::vector<int32_t>& box_and_goods,
							const int32_t& small_box_idx,
							const std::vector<int32_t>& goods,
							int32_t& goods_idx,
							std::vector<int32_t>& copy_boxes,
							int32_t& refurbish_goods_idx);
};
