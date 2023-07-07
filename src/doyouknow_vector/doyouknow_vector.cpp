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
		int size_limit = 2000000001;

		std::vector<int32_t> goods;
		std::vector<int32_t> boxes;
		std::vector<int32_t> save_box;

		goods.clear();
		boxes.clear();
		save_box.clear();

		goods.resize(item_count);
		boxes.resize(item_count);
		save_box.resize(item_count);

		for (int idx = 0; idx < item_count; idx++)
		{
			goods.at(idx) = (int32_t)(rand() % size_limit);
			boxes.at(idx) = (int32_t)(rand() % size_limit);
			save_box.at(idx) = (int32_t)(-1);
		}
		// Make data : <--

		for (int32_t goods_idx = 0; goods_idx < item_count; goods_idx++)
		{
			// Find box
			std::vector<int32_t> find_box_index =
				find_box(boxes, goods, goods_idx);

			// If not find box, next goods.
			if (find_box_index.size() == 0)
			{
				continue;
			}

			// Find small box
			int32_t last_small_box_index =
				find_last_small_box_index(boxes, find_box_index);

			// Input goods to box
			bool save_result =
				input_box(goods, goods_idx, last_small_box_index, save_box);

		}
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}

	return;
}

std::vector<int32_t> DOYOUKNOW_CLASS::find_box( const std::vector<int32_t>& boxes,
												const std::vector<int32_t>& goods,
												const int32_t& goods_idx)
{
	try {
		std::vector<int32_t> find_box_list;
		find_box_list.clear();
		for (int32_t iter = 0; iter < boxes.size(); iter++)
		{
			if (boxes.at(iter) >= goods.at(goods_idx))
			{
				find_box_list.push_back(iter);
			}			
		}

		return find_box_list;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

int32_t DOYOUKNOW_CLASS::find_last_small_box_index(	const std::vector<int32_t>& boxes,
													const std::vector<int32_t>& find_box_index)
{
	try {
		int32_t last_small_box_index = -1;
		int32_t box_size = boxes.at(find_box_index.front());
		for (int32_t iter = 0; iter < find_box_index.size(); iter++)
		{
			if (boxes.at(find_box_index.at(iter)) <= box_size)
			{
				last_small_box_index = find_box_index.at(iter);
				box_size = boxes.at(find_box_index.at(iter));
				//printf("small box index / size : [ %d / %d ]\n", last_small_box_index, box_size);
			}
		}

		return last_small_box_index;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

bool DOYOUKNOW_CLASS::input_box(	const std::vector<int32_t>& goods, 
									const int32_t& goods_idx,
									const int32_t& last_small_box_index,
									std::vector<int32_t>& save_box)
{
	try {
		bool save_result = false;
		if ( save_box.at(last_small_box_index) == -1 )
		{
			save_box.at(last_small_box_index) = goods.at(goods_idx);
			save_result = true;
			//printf("box index / goods size : [ %d / %d ]\n", last_small_box_index, goods.at(goods_idx));
		}
		return save_result;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
}

void main(void)
{
	struct bit_field_test
	{
		signed int a : 1; // Non-compliant
		signed int   : 1; // Compliant
		signed int   : 0; // Compliant
		signed int b : 2; // Compliant
		signed int   : 2; // Compliant
	};

	bit_field_test test_bf;
	test_bf.a = (int32_t)(-1);
	test_bf.b = 1;
	printf("%lld", test_bf.a);

	DOYOUKNOW_CLASS* do_you_know_ptr;
	do_you_know_ptr = new DOYOUKNOW_CLASS();

	do_you_know_ptr->std_vector();

	delete do_you_know_ptr;
	do_you_know_ptr = nullptr;

	return;
}