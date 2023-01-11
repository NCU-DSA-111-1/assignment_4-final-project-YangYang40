#  Arithmetic Coding vs Huffman Coding

## Compile & Run 

```sh
# Compile

##for arithmetic coding
gcc -o arcd arcd_stream.c arcd.c arcd.h adaptive_model.h adaptive_model.c 
##for huffman coding
gcc -o huffman huffcode.c huffman.c huffman.h 
ls
# Run
##for arithmetic coding
./arcd -e <testfilename | tee encodingtext
./arcd -d <encodingtext | tee decodingtext
##for huffman coding
./huffman -i testfilename -o encodingtext -c
./huffman -i encodingtext -o decodingtext -d
```



