#pragma once

template <class First, class Second, class Out>
void Merge(const First *first_begin, const First *first_end, const Second *second_begin, const Second *second_end,
           Out *out) {
  int i = 0, j = 0, k = 0;
  while (i < first_end - first_begin && j < second_end - second_begin) {
    if (*(first_begin + i) < *(second_begin + j)) {
      *(out + k) = *(first_begin + i);
      i++;
    } else {
      *(out + k) = *(second_begin + j);
      j++;
    }
    k++;
  }
  while (i < first_end - first_begin) {
    *(out + k) = *(first_begin + i);
    k++;
    i++;
  }
  while (j < second_end - second_begin) {
    *(out + k) = *(second_begin + j);
    k++;
    j++;
  }
}