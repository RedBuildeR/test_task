#include "Version1.h"
#include <math.h>

void Version1::round1()
{
	for (int i = 0; i < this->data.size(); i++) {
		for (int j = 0; j < this->data.size(); j++) {
			this->result_data.at(i, j) = this->is_visible2(i, j);
		}
	}
}

void Version1::round2()
{
	for (int k = 0; k < this->data.size(); k++) {
		for (int i = k, j = 0; i >= 0; i--, j++) {
			this->result_data.at(i, j) = this->is_visible2(i, j);
		}
	}
	for (int k = 1; k < this->data.size(); k++) {
		for (int i = this->data.size() - 1, j = k; j < this->data.size(); i--, j++) {
			this->result_data.at(i, j) = this->is_visible2(i, j);
		}
	}
}

bool Version1::is_visible1(int i, int j)
{
	bool result = true;
	int left_bound_i;
	int right_bound_i;
	int left_bound_j;
	int right_bound_j;
	if (this->point_i_index < i) {
		left_bound_i = this->point_i_index;
		right_bound_i = i;

	}
	else {
		left_bound_i = i;
		right_bound_i = this->point_i_index;
	}
	if (this->point_j_index < j) {
		left_bound_j = this->point_j_index;
		right_bound_j = j;

	}
	else {
		left_bound_j = j;
		right_bound_j = this->point_j_index;
	}
	// points in a row
	if (i == this->point_i_index) {
		for (int iter = left_bound_j + 1; iter < right_bound_j; iter++) {
			if ( !(this->data.at(i, iter) <= this->data.at(i, j) * 
				this->distance_ratio(0, iter, 0, j)) ) {
				result = false;
				break;
			}
		}
	}
	// points in a column
	if (j == this->point_j_index) {
		for (int iter = left_bound_i + 1; iter < right_bound_i; iter++) {
			if ( !(this->data.at(iter, j) <= this->data.at(i, j) *
				this->distance_ratio(iter, 0, i, 0)) ) {
				result = false;
				break;
			}
		}
	}
	// other cases
	if (abs(this->point_i_index - i) >= abs(this->point_j_index - j)) {
		for (int iter = left_bound_i + 1; iter < right_bound_i; iter++) {
			double line_j = ((double)j - this->point_j_index) * iter + 
				(i * this->point_j_index - j * this->point_i_index);
			line_j /= i - (double)this->point_i_index;
			int upper_point = (int)ceil(line_j);
			int lower_point = (int)floor(line_j);
			if ( !(this->data.at(iter, lower_point) <= this->data.at(i, j) *
				this->distance_ratio(iter, lower_point, i, j) ||
				this->data.at(iter, upper_point) <= this->data.at(i, j) *
				this->distance_ratio(iter, upper_point, i, j)) ) {
				result = false;
				break;
			}
		}
	}
	else {
		for (int iter = left_bound_j + 1; iter < right_bound_j; iter++) {
			double line_i = ((double)i - this->point_i_index) * iter + 
				(i * this->point_j_index - j * this->point_i_index);
			line_i /= j - (double)this->point_j_index;
			int upper_point = (int)ceil(line_i);
			int lower_point = (int)floor(line_i);
			if ( !(this->data.at(lower_point, iter) <= this->data.at(i, j) *
				this->distance_ratio(lower_point, iter, i, j) ||
				this->data.at(upper_point, iter) <= this->data.at(i, j) *
				this->distance_ratio(upper_point, iter, i, j)) ) {
				result = false;
				break;
			}
		}
	}
	return result;
}

bool Version1::is_visible2(int m, int n)
{
	bool result = true;
	int i = m;
	int j = n;
	if (this->point_i_index <= i && this->point_j_index < j) {
		if (i - this->point_i_index <= j - this->point_j_index) {
			while (i != this->point_i_index || j != this->point_j_index) {
				if (i - this->point_i_index >= (j - this->point_j_index) / 2.) {
					i--;
					j--;
				}
				else {
					j--;
				}
				if (i == this->point_i_index && j == this->point_j_index) {
					break;
				}
				if (!(this->data.at(i, j) <= this->data.at(m, n) *
					this->distance_ratio(i, j, m, n))) {
					result = false;
					break;
				}
			}
		}
		else {
			while (i != this->point_i_index || j != this->point_j_index) {
				if (j - this->point_j_index > (i - this->point_i_index) / 2.) {
					i--;
					j--;
				}
				else {
					i--;
				}
				if (i == this->point_i_index && j == this->point_j_index) {
					break;
				}
				if (!(this->data.at(i, j) <= this->data.at(m, n) *
					this->distance_ratio(i, j, m, n))) {
					result = false;
					break;
				}
			}
		}
	}
	else if (this->point_i_index > i && this->point_j_index <= j) {
		if (this->point_i_index - i <= j - this->point_j_index) {
			while (i != this->point_i_index && j != this->point_j_index) {
				if (this->point_i_index - i > (j - this->point_j_index) / 2.) {
					i++;
					j--;
				}
				else {
					j--;
				}
				if (i == this->point_i_index && j == this->point_j_index) {
					break;
				}
				if (!(this->data.at(i, j) <= this->data.at(m, n) *
					this->distance_ratio(i, j, m, n))) {
					result = false;
					break;
				}
			}
		}
		else {
			while (i != this->point_i_index || j != this->point_j_index) {
				if (j - this->point_j_index >= (this->point_i_index - i) / 2.) {
					i++;
					j--;
				}
				else {
					i++;
				}
				if (i == this->point_i_index && j == this->point_j_index) {
					break;
				}
				if (!(this->data.at(i, j) <= this->data.at(m, n) *
					this->distance_ratio(i, j, m, n))) {
					result = false;
					break;
				}
			}
		}
	}
	else if (this->point_i_index < i && this->point_j_index >= j) {
		if (i - this->point_i_index <= this->point_j_index - j) {
			while (i != this->point_i_index && j != this->point_j_index) {
				if (i - this->point_i_index > (this->point_j_index - j) / 2.) {
					i--;
					j++;
				}
				else {
					j++;
				}
				if (i == this->point_i_index && j == this->point_j_index) {
					break;
				}
				if (!(this->data.at(i, j) <= this->data.at(m, n) *
					this->distance_ratio(i, j, m, n))) {
					result = false;
					break;
				}
			}
		}
		else {
			while (i != this->point_i_index || j != this->point_j_index) {
				if (this->point_j_index - j >= (i - this->point_i_index) / 2.) {
					i--;
					j++;
				}
				else {
					i--;
				}
				if (i == this->point_i_index && j == this->point_j_index) {
					break;
				}
				if (!(this->data.at(i, j) <= this->data.at(m, n) *
					this->distance_ratio(i, j, m, n))) {
					result = false;
					break;
				}
			}
		}
	}
	else if (this->point_i_index >= i && this->point_j_index > j) {
		if (this->point_i_index - i <= this->point_j_index - j) {
			while (i != this->point_i_index || j != this->point_j_index) {
				if (this->point_i_index - i >= (this->point_j_index - j) / 2.) {
					i++;
					j++;
				}
				else {
					j++;
				}
				if (i == this->point_i_index && j == this->point_j_index) {
					break;
				}
				if (!(this->data.at(i, j) <= this->data.at(m, n) *
					this->distance_ratio(i, j, m, n))) {
					result = false;
					break;
				}
			}
		}
		else {
			while (i != this->point_i_index && j != this->point_j_index) {
				if (this->point_j_index - j > (this->point_i_index - i) / 2.) {
					i++;
					j++;
				}
				else {
					i--;
				}
				if (i == this->point_i_index && j == this->point_j_index) {
					break;
				}
				if (!(this->data.at(i, j) <= this->data.at(m, n) *
					this->distance_ratio(i, j, m, n))) {
					result = false;
					break;
				}
			}
		}
	}
	return result;
}

double Version1::distance_ratio(int i1, int j1, int i2, int j2)
{
	return sqrt(pow(this->point_i_index - i1,2) + pow(this->point_j_index - j1, 2)) /
		sqrt(pow(this->point_i_index - i2, 2) + pow(this->point_j_index - j2, 2));
}

Version1::Version1(const Matrix<int>& data, int point_i_index, int point_j_index)
{
	this->data = data;
	this->result_data = Matrix<bool>(this->data.size());
	this->point_i_index = point_i_index;
	this->point_j_index = point_j_index;
}


Matrix<int> Version1::get_data()
{
	return this->data;
}

Matrix<bool> Version1::get_map_visibility()
{
	this->round2();
	return this->result_data;
}
