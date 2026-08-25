#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <meta>
#include <vector>
#include <cassert>
#include <charconv>
#include <string_view>
#include <memory>
#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <limits>

struct simulation_config
{
  std::size_t adaptive_stepping_max;
  double solver_tolerance;
  std::size_t maximum_iterations;
  double time_step;
  double simulation_time;
  std::size_t output_interval;
};

xmlChar* find_element(xmlNodePtr parent, const char* tag)
{
    for (xmlNodePtr node = parent->children;
         node != nullptr;
         node = node->next)
    {
        if (node->type == XML_ELEMENT_NODE &&
            xmlStrcmp(node->name,
                      reinterpret_cast<const xmlChar*>(tag)) == 0)
        {
            return xmlNodeGetContent (node);
        }
    }

    return nullptr;
}

int main (int argc, char** argv)
{
  /* Instantiate the simulation object. */
  simulation_config sc{};

  /* Instantiate reflection object. */
  constexpr std::meta::info reflection = ^^simulation_config;

  /* Create context object. */
  constexpr std::meta::access_context ctx = std::meta::access_context::unchecked();

  /* Store the members in an array. */
  //constexpr std::span<const std::meta::info> members = std::define_static_array(std::meta::members_of(reflection, ctx));

  /* Instantiate XML reader. */
  xmlInitParser ();

  xmlDocPtr doc = xmlReadFile (argv[1], nullptr, 0);
  assert(doc != nullptr);

  xmlNodePtr root = xmlDocGetRootElement (doc);
  assert(root != nullptr);

  template for(constexpr auto& m : std::define_static_array(std::meta::members_of(reflection, ctx)))
  {
    if constexpr (std::meta::has_identifier(m))
    {
      constexpr auto type = std::meta::type_of(m);
      constexpr auto ptr = &[:m:];
      constexpr std::string_view tag = std::meta::identifier_of(m);
 
      xmlChar* str = find_element(root, tag.data());
      assert(str != nullptr);

      std::string_view text{reinterpret_cast<const char*>(str)};

      typename[:type:] val{};

      auto[end,err] = std::from_chars(text.data(), text.data() + text.size(), val);
      assert(err == std::errc());

      sc.*ptr = val;

      xmlFree(str);
    }
  }

  /* Finalize XML reader. */
  xmlFreeDoc(doc);
  xmlCleanupParser ();

  /* Print the config object. */
  std::cout << sc.adaptive_stepping_max << std::endl;
  std::cout << sc.solver_tolerance << std::endl;
  std::cout << sc.maximum_iterations << std::endl;
  std::cout << sc.time_step << std::endl;
  std::cout << sc.simulation_time << std::endl;
  std::cout << sc.output_interval << std::endl;

  return 0;
}
