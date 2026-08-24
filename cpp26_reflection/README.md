# C++26 Reflection

Code and presentation material for my talk on **Reflection in C++26**.

## About the Talk

Reflection has been one of the long-standing missing pieces of C++. With the introduction of compile-time reflection facilities in C++26, programs can inspect and manipulate their own structure during compilation.

This talk takes a **back-to-basics** approach to C++26 reflection, focusing on the key features of the `meta` library.

This talk offers an easy-to-understand example of XML file parsing using reflection.

## Acknowledgments

This talk was presented at an event organized by the **MUC++ community**
and hosted by **Brainlab AG**.

Many thanks to **Klaus Iglberger, Andreas Weis, and Miro Knejp** for
the opportunity to present and share this work with the C++ community.

## Topics

The talk covers:

* The reflection operator `^^`.
* The splice operator `[::]`.
* The Expansion Statements.
* A practical compile-time XML file parser.

## Repository Structure

```text
.
├── README.md
├── slides/
│   ├── reflection.tex
│   ├── references.bib
│   └── figures/
└── examples/
    ├── 01_reflection.cpp
    ├── 02_splicer.cpp
    ├── 03_xml_parser.cpp
```

## Requirements to build the examples

The examples use experimental C++26 reflection support and were developed
and tested with:

- **g++-16**

The XML example additionally requires the development headers and libraries
provided by `libxml2`.

> **Note:** C++26 reflection is a relatively new language feature and compiler support is still evolving. The examples may therefore require a sufficiently recent compiler or specific experimental compiler options.

## Building the Examples
To build ```01_reflection.cpp``` and ```02_splicer.cpp```  
```bash
g++-16 -std=c++26 -freflection path/to/source/file
```

To build ```03_xml_parser.cpp```
```bash
g++-16 -std=c++26 -freflection path/to/xml_parser.cpp $(pkg-config --cflags --libs libxml-2.0)
```
