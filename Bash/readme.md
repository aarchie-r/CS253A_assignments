# Assignment 2 - Shell Scripting

This Bash Script takes two arguments- input and output files.
The code can be executed by writing `bash lab.sh input_file.csv output_file.txt` in terminal with correct file paths and extension.
<br /><br />
The `input_file.csv` contains the list of colleges with columns as- Name, PredominantDegree, HighestDegree, FundingModel, Region, Geography, AdmissionRate,
ACTMedian, SATAverage, AverageCost, Expenditure, AverageFacultySalary, MedianDebt,
AverageAgeofEntry, MedianFamilyIncome, MedianEarnings.
<br /><br />

### Task 1
When the argument passed is not two, the script prints a usage message and exits as- 
```
Pls enter two different file names ass arguments as: bash lab.sh input_file.csv output_file.txt
where input_file.csv contains list of colleges with specipied columns
output_file.txt is the file which will contain the output
```

### Task 2
If the input file does
not exist, the script generates an appropriate error message and exits-
```
input_file.csv i.e., input file does not exist.
```

### Task 3
The list of colleges with columns- Name, PredominantDegree, HighestDegree, Region, Geography, AdmissionRate, AverageCost,
Expenditure gets printed with comma replaced by space

### Task 4
Next, the script saves the Name of the college whose HighestDegree is Bachelor’s to the output file as given in argument

### Task 5
Then, the script computes the average admission rate by grouping the colleges with respect to Geography
Column of the dataset and save it to the output file and gets it printed as- 
```
Geography: Average Admission Rate
Distant Rural: 0.64555
Distant Town: 0.66427
Fringe Rural: 0.640718
Fringe Town: 0.627744
```

### Task 6
The script saves the top five colleges to the output file who have maximum MedianEarnings.

<br />
Thus, all the required task gets executed and saved result can be accessed by `cat output_file.txt`
