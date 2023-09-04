#!/bin/bash
echo "Hello, world!"

# echo -e "You SHOULD input 2 numbers, I will multiplying them! \n"
# read -p "first number: " firstnu
# read -p "second number: " secnu
# total=$((${firstnu}*${secnu}))
# echo -e "\nThe result of ${firstnu} x ${secnu} is ==&gt; ${total}"

echo "Version1:" $(uname -r)
echo "Version2:" `uname -r`
echo "Data:" `date`
echo "Home:" ${HOME}