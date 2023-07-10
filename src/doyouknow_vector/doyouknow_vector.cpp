#include <doyouknow_vector.hpp>

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
	return;
}

void DOYOUKNOW_CLASS::std_vector(void)
{
	try {

		// Make data : -->
		srand((unsigned int)time(NULL));

		int32_t box_count			= 10000;
		int32_t box_size_limit		= 2000000000;
		int32_t small_box_idx		= 0;
		bool	input_result		= false;
		int32_t refurbish_goods_idx = 0;

		std::vector<int32_t>	goods;
		std::vector<int32_t>	boxes;
		std::vector<int32_t>	box_and_goods;

		goods.clear();
		boxes.clear();
		box_and_goods.clear();

		goods.resize(box_count);
		boxes.resize(box_count);
		box_and_goods.resize(box_count);

		for (int idx = 0; idx < box_count; idx++)
		{
			goods.at(idx) = (int32_t)((rand() % box_size_limit) + 1);
			boxes.at(idx) = (int32_t)((rand() % box_size_limit) + 1);
			box_and_goods.at(idx) = (int32_t)(0);
		}
		// Make data : <--

		std::vector<int32_t> find_box_idx;
		std::vector<int32_t> copy_boxes;
		find_box_idx.clear();
		find_box_idx.resize(box_count);
		for (int32_t goods_idx = 0; goods_idx < box_count; goods_idx++)
		{

			// Find box
			std::fill(find_box_idx.begin(), find_box_idx.end(), -1);
			find_box(goods, goods_idx, boxes, find_box_idx);

			// Find small box
			small_box_idx = 0;
			find_last_small_box_index(boxes, find_box_idx, small_box_idx);

			// Input goods to box
			input_result = false;
			input_box(goods, goods_idx, small_box_idx, box_and_goods, input_result);

			// Find next box
			copy_boxes = boxes;
			while (input_result == false)
			{
				find_next_box(box_and_goods, small_box_idx, goods, goods_idx, copy_boxes, refurbish_goods_idx);

				std::fill(find_box_idx.begin(), find_box_idx.end(), -1);
				find_box(goods, refurbish_goods_idx, copy_boxes, find_box_idx);

				if (find_box_idx.at(0) == -1)
				{
					printf("[ %10d / %10d ] : find box fail : goods index / goods size\n", goods_idx, goods.at(goods_idx));
					break;
				}

				small_box_idx = 0;
				find_last_small_box_index(copy_boxes, find_box_idx, small_box_idx);

				input_result = false;
				input_box(goods, refurbish_goods_idx, small_box_idx, box_and_goods, input_result);
			}

		}
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}

	return;
}

void DOYOUKNOW_CLASS::find_box(	const std::vector<int32_t>& goods,
								const int32_t& goods_idx,
								const std::vector<int32_t>& boxes,
								std::vector<int32_t>& find_box_idx)
{
	try {
		
		int32_t find_count = 0;

		for (int32_t iter = 0; iter < boxes.size(); iter++)
		{
			if (boxes.at(iter) >= goods.at(goods_idx))
			{
				find_box_idx.at(find_count) = iter;
				find_count++;
				// need to add overflow check : 'find_count'
			}			
		}

		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

void DOYOUKNOW_CLASS::find_last_small_box_index(	const std::vector<int32_t>& boxes,
													const std::vector<int32_t>& find_box_idx,
													int32_t& small_box_idx)
{
	try {

		if (find_box_idx.at(0) == -1)
		{
			; // Nothing
		}
		else
		{
			int32_t box_size = boxes.at( find_box_idx.at(0) );
			int32_t next_box_size = 0;
			for (int32_t iter = 0; iter < find_box_idx.size(); iter++)
			{
				if (find_box_idx.at(iter) == -1)
				{
					break;
				}

				next_box_size = boxes.at( find_box_idx.at(iter) );
				if (next_box_size <= box_size)
				{
					box_size = next_box_size;
					small_box_idx = find_box_idx.at(iter);
				}
			}
			//printf("[ %10d / %10d ] : small box index / box size\n", small_box_idx, box_size);
		}

		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

void DOYOUKNOW_CLASS::input_box(	const std::vector<int32_t>& goods, 
									const int32_t& goods_idx,
									const int32_t& small_box_idx,
									std::vector<int32_t>& box_and_goods,
									bool& input_result)
{
	try {

		if (box_and_goods.at(small_box_idx) == 0 )
		{
			box_and_goods.at(small_box_idx) = goods_idx;
			input_result = true;
			//printf("[ %10d / %10d ] : goods index / goods size\n", goods_idx, goods.at(goods_idx));
		}
		return ;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

void DOYOUKNOW_CLASS::find_next_box(	std::vector<int32_t>& box_and_goods,
										const int32_t& small_box_idx,
										const std::vector<int32_t>& goods,
										int32_t& goods_idx,
										std::vector<int32_t>& copy_boxes,
										int32_t& refurbish_goods_idx)
{
	try {

		if ( goods.at(goods_idx) < goods.at( box_and_goods.at(small_box_idx) ) )
		{
			refurbish_goods_idx = box_and_goods.at(small_box_idx);
			box_and_goods.at(small_box_idx) = goods_idx;
		}
		else
		{
			refurbish_goods_idx = goods_idx;
		}

		copy_boxes.at(small_box_idx) = 0;

		return ;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

void main(void)
{

	DOYOUKNOW_CLASS* do_you_know_ptr;
	do_you_know_ptr = new DOYOUKNOW_CLASS();

	do_you_know_ptr->std_vector();

	delete do_you_know_ptr;
	do_you_know_ptr = nullptr;

	return;
}