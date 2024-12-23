#include <stdio.h>
#include <string.h>

// Function to get value of a Roman numeral
int getRomanValue(char roman) {

    // Return the corresponding decimal value for a roman numeral character
    switch (roman) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return -1;                   // Return -1 for invalid Roman numeral
    }
}

// Function to convert Roman numeral to decimal
int romanToDecimal(char roman[]) {
    int result = 0;                                     // Initialize result to 0
    for (int i = 0; roman[i] != '\0'; i++) {            // Loop through each character of the Roman numeral in string
        int current = getRomanValue(roman[i]);          // Get the value of the current Roman numeral
        if (current == -1) {                            // Check if the numeral is invalid
            return -1;                                  // Return -1 if an invalid Roman numeral is encountered
        }

        int next = getRomanValue(roman[i + 1]);         // Get the value of the next Roman numeral
        if (next > current) {                           // Check if subtraction rule applies
            result += (next - current);                 // Add the difference
            i++;                                        // Skip the next numeral as it is already processed
        } else {
            result += current;                          // Add the current numeral to the result
        }
    }
    return result;                                      // Return the decimal equivalent of the Roman numeral
}


// Helper function to print numbers in words recursively
void numberToWordsHelper(int num, FILE *outFile) {
    if (num >= 1000000) {                                   // Check for millions
        numberToWordsHelper(num / 1000000, outFile);        // Processed millions part
        fprintf(outFile, "Million ");
        num %= 1000000;                                     // Update the number to the remainder
    }
    if (num >= 1000) {                                      // Check for thousands
        numberToWordsHelper(num / 1000, outFile);           // Processed thousands part
        fprintf(outFile, "Thousand ");
        num %= 1000;                                        // Update the number to the remainder
    }
    if (num >= 100) {                                       // Check for hundreds
        numberToWordsHelper(num / 100, outFile);            // Process hundreds part
        fprintf(outFile, "Hundred ");                       
        num %= 100;                                         // Update the number to the remainder
    }                   
    if (num >= 20) {                                        // Check for tens greater than 20
        const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        fprintf(outFile, "%s ", tens[num / 10]);            // Write tens in words
        num %= 10;                                          // Update the number of remainder
    }
    if (num >= 10 && num < 20) {                            // Check for numbers between 10 and 19
        const char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        fprintf(outFile, "%s ", teens[num - 10]);            // Write teens in words
        return;
    }
    if (num > 0) {                                          // Check for single digits
        const char *units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
        fprintf(outFile, "%s ", units[num]);                // Write the unit word
    }
}

// Wrapper function for number to words
void numberToWords(int num, FILE *outFile) {
    if (num == 0) {                                         // Check if the number is zero
        fprintf(outFile, "Zero");                           // Write "Zero" to the output
        return;
    }
    if (num < 0) {                                         // Check if the number is negative
        fprintf(outFile, "Negative ");                     // Write "Negative" to the output
        num = -num;                                        // Convert negative number to positive for word conversion
    }
    numberToWordsHelper(num, outFile);
}

// Perform basic arithmethic operations                    
int calculate(int num1, int num2, char operator) {
    switch (operator) {                                    // Determine the operation based on the operator
        case '+': return num1 + num2;                      // Addition
        case '-': return num1 - num2;                      // Subtraqction
        case '*': return num1 * num2;                      // Multiplication
        case '/': return num2 != 0 ? num1 / num2 : 0;      // Division with zero check
        default: return 0;
    }
}

int main() {
    FILE *inFile, *outFile;                                // Declare file pointers for input and output files
    char line[200], roman1[50], roman2[50], operator;      // Buffers to store input and parsed data

    // Open input file for reading
    inFile = fopen("input.txt", "r");                     
    if (inFile == NULL) {                                  // Check if the input file could not be opened
        printf("Error opening input file!\n");
        return 1;
    }

    // Open output file for writing             
    outFile = fopen("output.txt", "w");                    // Check if the output file could not be opened
    if (outFile == NULL) {
        printf("Error opening output file!\n");
        fclose(inFile);                                    // Close the input file
        return 1;
    }

    // Read and process each line from the input file
    while (fgets(line, sizeof(line), inFile)) {                     
        sscanf(line, "%s %c %s", roman1, &operator, roman2);        // Parse the line into Roman numerals and operator

        // Convert Roman numerals to decimal    
        int num1 = romanToDecimal(roman1);                          // Convert first Roman numeral to decimal
        int num2 = romanToDecimal(roman2);                          // Convert second Roman numeral to decimal

        // Check if the Roman numerals are valid
        if (num1 == -1 || num2 == -1) {                             
            fprintf(outFile, "Invalid Roman Numeral\n");            // Write an error message to the output file
        } else {
            // Perform calculation
            int result = calculate(num1, num2, operator);           // Perform the calculation

            // Convert result to words and write to output file
            numberToWords(result, outFile);                         // Convert the result to words and write to the output file
            fprintf(outFile, "\n");                                 // Add a newline after the result
        }
    }

    // Close files
    fclose(inFile);                  // Close the input file
    fclose(outFile);                // Close the output file
    printf("Results are processed. Check the results in the output.txt file\n");            // Notify the user

    return 0;                       // Exit the program
}
