#!/bin/bash
shopt -s extglob dotglob;

cd ../get_next_line-00;
rm -rf !(.git)

cd ../codam-get_next_line;
for file in $(git ls-tree -r HEAD --name-only task);
	do cp $file ../get_next_line-00;
done;

cd ../get_next_line-00;
git add .;
git commit -m "$1";
git push;
