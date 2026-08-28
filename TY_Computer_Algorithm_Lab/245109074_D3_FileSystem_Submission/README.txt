D3 Collaborative Document Track-Changes Diff Tool
PRN: 245109074
Name: Atharv Kulkarni

FILES
-----
d3.cpp
test1_v1.txt, test1_v2.txt
test2_v1.txt, test2_v2.txt
test3_v1_empty.txt, test3_v2.txt
test4_v1.txt, test4_v2.txt
test5_v1.txt, test5_v2.txt
hots_base.txt, hots_v1.txt, hots_v2.txt

COMPILE
-------
g++ -std=c++17 d3.cpp -o d3

TWO-WAY RUNS
------------
./d3 test1_v1.txt test1_v2.txt
./d3 test2_v1.txt test2_v2.txt
./d3 test3_v1_empty.txt test3_v2.txt
./d3 test4_v1.txt test4_v2.txt
./d3 test5_v1.txt test5_v2.txt

HOTS / THREE-WAY RUN
--------------------
./d3 hots_base.txt hots_v1.txt hots_v2.txt

FILE FORMAT
-----------
First line = number of paragraphs.
Following lines = one paragraph per line.

WHY FILE INPUT?
---------------
The program demonstrates basic C++ file-system/file-I/O usage through ifstream.
Each document version is stored as an independent .txt file, making the diff
engine closer to a real document-versioning workflow.

IMPORTANT
---------
The program expects one paragraph per line. Do not put blank lines inside a
paragraph for these test files.
