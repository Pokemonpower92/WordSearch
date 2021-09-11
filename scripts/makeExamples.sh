#!/bin/bash
SOLUTIONS_DIR=solutions
EXAMPLES_DIR=examples
JGRAPH_DIR=jgraph
SEARCHES_DIR=searches

files=`(cd "$EXAMPLES_DIR" && ls)`
for filename in $files; do 
    ./bin/MakeSearch -a "$SOLUTIONS_DIR"/"$filename".jgr -s 20 < \
                        "$EXAMPLES_DIR"/"$filename" >  \
                        "$JGRAPH_DIR"/"$filename".jgr

    jgraph -P "$SOLUTIONS_DIR"/"$filename".jgr | \
        ps2pdf - | \
        convert -density 300 - -quality 100 "$SOLUTIONS_DIR"/"$filename".jpg

    jgraph -P "$JGRAPH_DIR"/"$filename".jgr | \
        ps2pdf - | \
        convert -density 300 - -quality 100 "$SEARCHES_DIR"/"$filename".jpg
done