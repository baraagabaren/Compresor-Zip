# 📂 LZ77 Compressor in C

A simple command-line tool that compresses and decompresses text files using the LZ77 compression algorithm.

Features

📦 Compresses any text file to .bin format

🔁 Decompresses .bin files back to the original

🖥 Interactive terminal UI (z to compress, u to decompress)

🗂 Built as a reusable static library (libzip.a)

File Structure

zip.c, unzip.c – Compression and decompression logic

Zipp.h – Header file for the public API

main.c – Simple interface to interact with the user

libzip.a – Compiled static library

How to Compile

gcc -c zip.c -o zip.o
gcc -c unzip.c -o unzip.o
ar rcs libzip.a zip.o unzip.o
gcc main.c -L. -lzip -o compress_tool

Usage

./compress_tool
for zip enter z ,for unzip enter u : z
file name : hobbit.txt

./compress_tool
for zip enter z ,for unzip enter u : u
compressed file name (without .bin): compres

Output

Compressed file: compres.bin

Decompressed file: output.txt

Made by Baraa 🚀

