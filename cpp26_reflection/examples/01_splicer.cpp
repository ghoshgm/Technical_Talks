#include <meta>
#include <vector>
#include <cassert>

struct vector
{
  double x, y, z;
};

int main()
{
  /* Type deduction. */
  const auto a = 42;             /* Same as: const int a = 42  */
  constexpr std::meta::info type = std::meta::type_of(^^a);
  typename[:type:] x = 42;       /* Same as: const int x = 42; */
  static_assert(is_integral_type(type_of(^^x)) == true);
  static_assert(is_const(type_of(^^x)));

  /* Addressed splicing. */
  vector v{};
  constexpr auto ptr = &[:^^vector::x:];    /* Same as: constexpr double vector::* ptr = &vector::x;  */
  static_assert(is_member_pointer_type(type_of(^^ptr)));
  v.*ptr = 42.0;                              /* Same as: v.x = 42.0; */
  assert(v.x == 42.0);

  return EXIT_SUCCESS;
}
