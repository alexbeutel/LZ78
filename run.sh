echo "COMPRESS"
./lz78 -e < "$1" > "tests/$1.lz78"
echo "UNCOMPRESS"
./lz78 -d < "tests/$1.lz78" > "tests/uncompressed_$1"
echo "DIFF"
diff "$1" "tests/uncompressed_$1"

