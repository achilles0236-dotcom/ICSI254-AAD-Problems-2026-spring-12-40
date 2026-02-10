#!/bin/bash

gcc -o palindrome palindrome.c -lm
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

passed=0
failed=0

for input in tests/input*.txt; do
    num=$(echo $input | grep -o '[0-9]*')
    output="tests/output${num}.txt"
    
    echo "Running test $num..."
    
    actual=$(./palindrome < $input)
    expected=$(cat $output)
    
    if [ "$actual" == "$expected" ]; then
        echo "✓ Test $num passed"
        ((passed++))
    else
        echo "✗ Test $num failed"
        echo "  Expected: $expected"
        echo "  Got: $actual"
        ((failed++))
    fi
done

rm palindrome

echo ""
echo "Results: $passed passed, $failed failed"

if [ $failed -gt 0 ]; then
    exit 1
fi
