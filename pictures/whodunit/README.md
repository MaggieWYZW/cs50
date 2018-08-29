# Questions

## What's `stdint.h`?
It is a header file in C programming library.  It defines the exact-width of different integer types. In bmp.h, including this library allows to define in types of a specific length.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
These data types are from 'stdint.h' used to define the length of a data type. They give us the flexibility to define data types of desired width.
Because there are times that a 4bit default integer is too small to store a large value. By using 'int32_t' a signed int of 32 bits is defined.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
- 'BYTE': 8 bits = 1 bytes
- 'DWORD': 32 bits = 4 bytes
- 'LONG': 32 bits = 4 bytes
- 'WORD': 16 bits = 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
The first 2 bytes should store the variable called bfType which declares the type of the file.
The hexadecimal value for the two bytes is 0x424d.


## What's the difference between `bfSize` and `biSize`?
'bfSize' is the size of the bitmap file, including pixels, paddings and headers.
'biSize' is the size of the structure itself.
'bfSize' = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

## What does it mean if `biHeight` is negative?
 If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the lower-left corner.
 If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.


## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
'biBitCount' represents the number of bits-per-pixel. The value must be one of the predefined values.


## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
If the file doesn't exists then the pointer reading the file returns to NULL;
If there is no memory usable, then the pointer returen to NULL when trying to write to a file.

## Why is the third argument to `fread` always `1` in our code?
THe third argument is the number of files to read. In our code, we only read one file at a time, therefore the value is always 1.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
Only one byte is added to the image, therefore padding = 1.


## What does `fseek` do?
It locates where the pointer is when reading from or writing to a file.


## What is `SEEK_CUR`?
The third argument of 'fseek' refers to the position where we want to skip from in the file.
'SEEK_CUR' is defined by the function, which means current position of the file pointer.
This means we skip the pixels starting from where the image is padded.

## Whodunit?

TODO
