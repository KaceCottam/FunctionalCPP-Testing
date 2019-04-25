#include <fmt/format.h>
#include <fplus/fplus.hpp>
using namespace fmt;
using namespace fplus;

namespace fmt {
template <>
template <typename T1, typename T2>
struct formatter<std::pair<T1, T2>> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) {
    return ctx.begin();
  }

  template <typename FormatContext>
  constexpr auto format(const std::pair<T1, T2> &p, FormatContext &ctx) {
    return format_to(ctx.begin(), "( {}, {} )", p.first, p.second);
  }
};
}  // namespace fmt

int main(int argc, char **argv) {
  const auto make_numbers = [](const int min, const int max) {
    print("This is a carethesian product of two sets of {}-{}.\n", min, max);
    return numbers(min, max + 1);
  };
  std::vector<int> numbers;
  if (argc == 3) {
    numbers = make_numbers(atoi(argv[1]),atoi(argv[2]));
  } else {
    numbers = make_numbers(0, 5);
  }
  print("These are the numbers of each set {}.\n", show_cont(numbers));

  const auto product = carthesian_product(numbers, numbers);

  print("This is the cartesian product {}\n", show_cont(product));

  const auto sqrd_product = 
            transform(fwd::transform_pair(square<int>, square<int>), product);

  print("This is the square of the product {}\n", show_cont(sqrd_product));
}