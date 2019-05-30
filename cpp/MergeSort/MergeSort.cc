#include "3rdParty/Catch.hh"

#include <vector>
#include <cstdint>

using namespace std;

namespace Algorithm
{
namespace Impl
{
/// @brief Merge two sorted array and return merged result.
/// @return Merged results.
template<class T>
vector<T> merge(const vector<T>& sorted_lhs, const vector<T>& sorted_rhs)
{
  vector<T> merged_res;
  merged_res.reserve(sorted_lhs.size() + sorted_rhs.size());

  uint32_t i = 0U, j = 0U;
  while(i < sorted_lhs.size() && j < sorted_rhs.size())
  {
    if(sorted_lhs[i] < sorted_rhs[j])
    {
      merged_res.push_back(sorted_lhs[i++]);
    }
    else
    {
      merged_res.push_back(sorted_rhs[j++]);
    }
  }

  while(i < sorted_lhs.size())
  {
    merged_res.push_back(sorted_lhs[i++]);
  }

  while(j < sorted_rhs.size())
  {
    merged_res.push_back(sorted_rhs[j++]);
  }

  return merged_res;
}

/// @brief Merge sort recursion function.
/// @return Sorted array.
template<class T>
vector<T> merge_sort(const vector<T>& input, uint32_t i, uint32_t j)
{
  if(i == j)
  {
    return {input[i]};
  }

  const uint32_t mid = (static_cast<int64_t>(i) + static_cast<int64_t>(j)) / 2;
  
  const auto sorted_lhs = merge_sort(input, i, mid);
  const auto sorted_rhs = merge_sort(input, mid + 1, j);
  
  return merge(sorted_lhs, sorted_rhs);
}
}

/// @brief Merge sort algorithm.
/// @return Sorted array.
template<class T>
vector<T> merge_sort(const vector<T>& input)
{
  if(input.empty())
  {
    return {};
  }

  return Impl::merge_sort(input, 0U, input.size() - 1);
}
}

TEST_CASE("Test merge sort")
{
  SECTION("Test empty array")
  {
    REQUIRE(Algorithm::merge_sort(vector<int32_t>{}) == vector<int32_t>{});
  }

  SECTION("Test integer array")
  {
    vector<int32_t> input{1,5,7,3,12,3,10};
    const vector<int32_t> ans{1,3,3,5,7,10,12};
    REQUIRE(Algorithm::merge_sort(input) == ans);
  }

  SECTION("Test float array")
  {
    vector<float> input{2.8f,1.3f,20.3f, 8.9f, 12.5f};
    const vector<float> ans{1.3f, 2.8f, 8.9f, 12.5f, 20.3f};
    REQUIRE(Algorithm::merge_sort(input) == ans);
  }
}
