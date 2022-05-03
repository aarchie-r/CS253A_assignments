#!/bin/bash

if [ $# -ne 2 ]; then
    #to print the user message of how to give command to run the bash script when two arguments are not given
    echo $#
    echo "Pls enter two different file names ass arguments as: bash lab.sh input_file.csv output_file.txt"
    echo "where input_file.csv contains list of colleges with specipied columns"
    echo "output_file.txt is the file which will contain the output"
    exit 1
fi

files=("$@")
in_file=${files[0]} #to save the input file in a variable
out_file=${files[1]} #to save the output file in a variable


if [ -f "$in_file" ]; then
    # to proceed when the file exists

    #printing in the file with given columns for all colleges
    awk -F',' '{print $1,$2,$3,$5,$6,$7,$10,$11}' $1 > names.txt
    cp $1 total.txt   # to copy the record temporary from output file to total.txt so created
    cp names.txt $2  # storing the required info of colleges in output file

    #the name of colleges with highest degree as "Bachelor's"

    grep -w "Bachelor's" total.txt > names.txt #to get lines with "Bachelor's"  in it

    echo "" >> $2
    echo "" >> $2
    echo "Colleges whose HighestDegree is Bachelor’s-" >> $2

    awk -F',' '{print $1}' names.txt >> $2 # to print the name of colleges with highest degree as "Bachelor's"

    #getting the average admission rate geography wise

    awk -F',' '{print $6}' total.txt > names.txt # printing the geography of all colleges in names.txt
    sort names.txt | uniq > output.txt # printing the unique geography in sorted order in output.txt

    geo=()  #to store the unique geography
    while IFS= read -r line 
    do
        geo+=("$line")
    done < output.txt


    echo "" >> $2
    echo "" >> $2
    echo "Geography: Average Admission Rate" >> $2

    for city in "${geo[@]}"
    do  
        if [ "$city" == "Geography" ]; then #in case the geography is geography means it is the title one so not counted
            continue
        fi
        grep -w "$city" total.txt > output.txt #taking the geography city one by one and checking for all colleges with that geography
        avg=$(awk -F',' '{ total += $7; count++ } END { print total/count}' output.txt) #for taking the 7th column of admission rate and finding avg after summing up the admission rate
        echo "$city: $avg" >> $2 #printing the avg and the respective geography in output file
    done

    #to get top five colleges with respect of median earnings

    awk -F',' '{print $1,$16}' total.txt > names.txt #to print the columns of names and median earnings
    awk '{print $(NF),$0}' names.txt| sort -n -r| cut -f2- -d' ' > output.txt #to take the last column (median earnings) keep at 0th place to sort and again placing it back

    colleges=() # to store the colleges and their median earnings
    count=0
    while IFS= read -r line 
    do
        colleges+=("$line")
        ((count++))
        if [ "$count" == '5' ]; then
            # to store only five colleges
            break
        fi
    done < output.txt

    echo "" >> $2
    echo "" >> $2
    echo "Colleges MedianEarnings" >> $2

    for name in "${colleges[@]}"
    do
        #printing the names of colleges
        echo "$name" >> $2
    done

    #removing the misllaneous files
    rm names.txt
    rm total.txt
    rm output.txt


else 
    #to print when the input file doesn't exist
    echo "$in_file i.e., input file does not exist."
    exit 1
fi