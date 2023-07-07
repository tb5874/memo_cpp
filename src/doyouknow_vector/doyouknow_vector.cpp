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

		int item_count = 100000;
		int size_limit = 2000000000;

		std::vector<int32_t>	goods;
		std::vector<int32_t>	boxes;
		std::vector<int32_t>	find_box_idx;
		int32_t					small_box_idx = 0;
		std::vector<int32_t>	box_and_goods;

		goods.clear();
		boxes.clear();
		find_box_idx.clear();
		box_and_goods.clear();

		goods.resize(item_count);
		boxes.resize(item_count);
		find_box_idx.resize(item_count);
		box_and_goods.resize(item_count);

		for (int idx = 0; idx < item_count; idx++)
		{
			goods.at(idx) = (int32_t)((rand() % size_limit) + 1);
			boxes.at(idx) = (int32_t)((rand() % size_limit) + 1);
			find_box_idx.at(idx) = -1;
			box_and_goods.at(idx) = (int32_t)(0);
		}
		// Make data : <--

		for (int32_t goods_idx = 0; goods_idx < item_count; goods_idx++)
		{

			// Find box
			std::fill(find_box_idx.begin(), find_box_idx.end(), -1);
			find_box(goods, goods_idx, boxes, find_box_idx);

			// Find small box
			small_box_idx = 0;
			find_last_small_box_index(boxes, find_box_idx, small_box_idx);

			// Input goods to box
			input_box(goods, goods_idx, small_box_idx, box_and_goods);

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
					small_box_idx = iter;
				}
			}
			printf("small box index / box size : [ %d / %d ]\n", small_box_idx, box_size);
		}

		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

bool DOYOUKNOW_CLASS::input_box(	const std::vector<int32_t>& goods, 
									const int32_t& goods_idx,
									const int32_t& small_box_idx,
									std::vector<int32_t>& box_and_goods)
{
	try {
		bool save_result = false;
		if (box_and_goods.at(small_box_idx) == 0 )
		{
			box_and_goods.at(small_box_idx) = goods.at(goods_idx);
			save_result = true;
			printf("goods size : [ %d ]\n", goods.at(goods_idx));
		}
		return save_result;
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