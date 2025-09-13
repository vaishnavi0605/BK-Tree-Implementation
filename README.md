## BK-Tree_Implementation

## 1. Overview:

This project implements a dual-function BK Tree (Burkhard-Keller Tree) system. The BK Tree, a data structure designed for discrete metric spaces, has been adapted here for two purposes: performing approximate string matching for words and managing geographic data on hospitals. In the words application, the BK Tree 
facilitates approximate matching, common in applications like spell checkers and auto-complete, by finding words within a specified Levenshtein distance. For hospital recommendation, it finds nearby hospitals based on geographic coordinates, using haversine distance to calculate proximity. 

## 2. Project Structure:

```bash
/BK-Tree_Implementation
├── BK_structure.c                      # Defines BK Tree structure and functions for approximate word matching.
├── dictionary.c                        # Loads a dictionary file into the BK Tree for word matching.
├── levenshtein.c                       # Implements the basic Levenshtein Distance calculation.
├── Ukkonen_Levenshtein_Distance.c      # Implements Ukkonen's optimized Levenshtein algorithm.
├── dictionary.txt                      # Sample dictionary file for words.
├── Hosp_BK_structure.c                 # Defines BK Tree structure and functions for hospital proximity search.
├── hospital_data.csv                   # Sample CSV file with hospital names, latitudes, and longitudes.
├── header.h                            # Contains function prototypes, macros, and struct definitions.
└── README.md                           # Documentation file with project details, structure, and usage.
```

## 3. File Descriptions:

3.1 **BK_structure.c**: Contains the core BK Tree structure and operations for managing words, including:

createNode: Initializes nodes representing each word in the BK Tree. <br/>
insertNode: Inserts words based on Levenshtein distance, grouping words by similarity. <br/>
depth_traverse: Traverses the BK Tree to display words, helpful for testing and visualization. <br/>
approximateSearch: Finds words within a given Levenshtein distance of a query, supporting approximate string matching. <br/>
autocomplete: Suggests words based on a prefix, enhancing user experience in applications like auto-complete. <br/>

3.2 **dictionary.c**: Loads words from dictionary.txt into the BK Tree for word-based approximate matching. It includes helper functions to load words into an array and insert them into the BK Tree.

3.3 **levenshtein.c**: Implements the basic Levenshtein Distance algorithm, calculating the edit distance between words for approximate matching.

3.4 **Ukkonen_Levenshtein_Distance.c**: Provides an optimized Levenshtein Distance calculation using Ukkonen's algorithm, offering faster searches in large dictionaries.

3.5 **dictionary.txt**: A sample file with words to populate the word BK Tree, supporting approximate matching tests.

3.6 **Hosp_BK_structure.c**: Contains the BK Tree structure and functions for managing hospital data. Key functions include:

createNode: Creates a node for each hospital with its name, latitude, and longitude. <br/>
haversine_distance: Calculates geographic distance between nodes. <br/>
insertNode: Inserts hospitals based on geographic distances. <br/>
depth_traverse: Traverses the BK Tree to display hospital names. <br/>
searchBKTree: Finds hospitals within a given distance range from specified coordinates. <br/>
read_csv: Loads hospital data from hospital_data.csv into the BK Tree. <br/>

3.7 **hospital_data.csv**: A sample CSV file containing hospital data with names, latitudes, and longitudes, used to build the hospital BK Tree for proximity searches.

3.8 **header.h**: A centralized header that includes macros, constants, and function prototypes for the entire project. Key elements include:

Macros for utility functions like MAX and MIN and useful constants, such as M_PI. <br/>
NODE_CAPACITY for restricting each node to a set number of children. <br/>
Struct definitions for nodes in both hospital and word trees, containing fields for longitude, latitude, and name (in hospital BK Tree) or word (in the word BK Tree). <br/>
Function prototypes for hospital and word operations, such as createNode, insertNode, haversine_distance, lev_dist, and UK_lev_dist, as well as memory management functions to ensure proper resource usage. <br/>

## 4. Features:

**Word Matching:**
Insertion: Adds words to the BK Tree based on Levenshtein distance. <br/>
Approximate Search: Finds words within a specified Levenshtein distance. <br/>
Autocomplete: Suggests words based on a given prefix. <br/>
Levenshtein Distance Calculations: Includes both basic and optimized (Ukkonen's) versions. <br/>

**Hospital Search:**
Insertion: Adds hospitals to the BK Tree based on geographic (haversine) distance. <br/>
Proximity Search: Finds hospitals within a specified distance range from a location. <br/>
Traversal: Traverses the tree to display hospital names. <br/>

## 5. Installation and Compilation:

To compile and run the project, use the following commands:

```bash
gcc BK_structure.c dictionary.c Ukkonen_Levenshtein_Distance.c -o word_bk_tree
./word_bk_tree
```
(for spell-checker)

```bash
gcc Hosp_BK_structure.c -o hosp_bk_tree
./hosp_bk_tree
```
(for hospital recommendation)

Ensure dictionary.txt and hospital_data.csv are in the same directory as the executables to load data successfully.

## 6. Memory Management:

Both the word and hospital trees use dynamic memory allocation for nodes and child pointers. Ensure adequate memory is available for large datasets. A memory cleanup function (free_tree) is provided to release allocated memory after execution, preventing memory leaks.

## 7. Node Capacity:

Each BK Tree node is limited to a fixed number of child nodes for simplicity. In the word BK Tree, NODE_CAPACITY is set to 15 to maintain manageable branching levels, while the hospital BK Tree uses 23 child nodes for distance partitioning, facilitating efficient traversal and search in both applications.
