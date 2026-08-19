<a id="readme-top"></a>

<!-- PROJECT LOGO -->
<div align="center">
  <a href="https://github.com/jerichd4c/circular-linked-list-assignment">
    <img src="https://raw.githubusercontent.com/jerichd4c/ReflexJDBC/main/cpp_logo.svg" alt="Logo" width="80" height="80">
  </a>
</div>


<div align="center">
  <h3 align="center">Circular Linked List Assignment</h3>

  <p align="center">
    A C++ project demonstrating circular linked list implementations (simple and doubly) for managing person data.
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>

## About The Project

This project contains C++ implementations of circular linked lists for managing person data:

- **`listaCircularSimplePersonas.cpp`**: Implements a singly circular linked list with operations for inserting, deleting, searching, and file persistence.
- **`listaCircularPersonasDoblementeEnlazada.cpp`**: Implements a doubly circular linked list with bidirectional traversal, offering the same operations plus reverse display.

Each implementation includes:
- Insert at beginning/end
- Insert at random position
- Insert between two nodes
- Delete by name
- Search by ID
- Display list (forward/reverse for doubly)
- File persistence (CSV format)

### Built With

* [![C++][Cpp-shield]][Cpp-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Getting Started

To get a local copy up and running, compile the source code natively via GCC/G++.

### Prerequisites

* GCC / G++ (MinGW on Windows)
* C++11 or higher

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/jerichd4c/circular-linked-list-assignment.git
   ```
2. Navigate to the project directory
   ```sh
   cd circular-linked-list-assignment
   ```
4. Compile the simple list version:
   ```sh
   g++ listaCircularSimplePersonas.cpp -o output/listaCircularSimplePersonas.exe
   ```
5. Compile the doubly linked list version:
   ```sh
   g++ listaCircularPersonasDoblementeEnlazada.cpp -o output/listaCircularPersonasDoblementeEnlazada.exe
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Usage

Execute the preferred binary to run the interactive console environment:

1. Copy the desired data file from `archivos_de_personas/listaOrdenada/` or `archivos_de_personas/listaDesordenada/` to the `output/` folder
2. Run the executable from the `output/` folder
3. Select from the menu options

```sh
# Run Simple Circular List
./output/listaCircularSimplePersonas.exe

# Run Doubly Circular List
./output/listaCircularPersonasDoblementeEnlazada.exe
```

### Data File Format

```
ID;nombre;apellido;edad;genero;altura
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## License

Distributed under the MIT License.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
[Cpp-shield]: https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white
[Cpp-url]: https://isocpp.org/
