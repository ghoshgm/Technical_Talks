#include <meta>
#include <array>
#include <iostream>

struct vector
{
  double x, y, z;
};

int main()
{
  /* Create reflection of vector */
  constexpr std::meta::info r = ^^vector;

  /* Set unrestricted access. */
  constexpr std::meta::access_context ctx = std::meta::access_context::unchecked();

  /* Loop over the member variables of vector. */
  template for( constexpr auto& m : std::define_static_array(std::meta::members_of(r, ctx)) )
  {
    if constexpr (std::meta::has_identifier(m))
    {
      constexpr std::string_view identifier = std::meta::identifier_of(m);
      std::cout << identifier << '\n';
    }
  }

  return EXIT_SUCCESS;
}
