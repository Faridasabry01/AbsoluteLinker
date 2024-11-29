# Two Pass Assembler
### Modi-SIC Assembler

This repository contains a simulation of an assembler for the **Modified Simple Instruction Computer (Modi-SIC)**. It processes Modi-SIC assembly code and generates intermediate files, symbol tables, object code, and HTE records.

## Features
- **Intermediate File Generation**: Removes comments and line numbers from the assembly code.
- **Pass 1**: 
  - Generates a location counter for program lines.
  - Creates a symbol table for labels.
- **Pass 2**:
  - Produces object code.
  - Generates HTE (Header, Text, End) records.
- **Instruction Handling**:
  - Supports Format 1 and Format 3 instructions.
  - Processes immediate instructions (`#` prefix).
  - Handles memory directives (`BYTE`, `WORD`, `RESB`, `RESW`).

---

## Steps to Run the Program

### 1. Prepare the Input File
- Create a file named `in.txt` containing the Modi-SIC assembly code.
- The input file should follow the correct Modi-SIC format.
- Example `in.txt` content:

### 2. Compile the Program
- Ensure all source code files (`main.cpp`, `codes1.h`, `codes2.h`, `codes3.h`) are in the same directory.
- Use a C++ compiler to compile the program. For example:
```bash
g++ main.cpp -o modi_sic_assembler
 ```

### 3. Run the Program
To execute the program, ensure you have compiled it and have the input file `in.txt` in the same directory. Run the program using the following command:

```bash
./modi_sic_assembler
```

### 4. Check the Output
After running the program, several output files will be generated in the working directory. Each file serves a specific purpose in the assembly process:

1. **`intermediate.txt`**:
   - This file contains the cleaned assembly code without comments and line numbers.
   - Example:
     ```
     COPY    START   1000
     FIRST   STL     RETADR
     CLOOP   JSUB    RDREC
             LDA     #3
             COMP    ZERO
             JEQ     ENDFIL
             JSUB    WRREC
             J       CLOOP
     ENDFIL  LDA     EOF
             STA     BUFFER
             END     FIRST
     ```

2. **`symbTable.txt`**:
   - A symbol table listing all labels and their corresponding addresses.
   - Example:
     ```
     FIRST   1000
     CLOOP   1003
     ENDFIL  1015
     EOF     102a
     THREE   102d
     ZERO    1030
     RETADR  1033
     LENGTH  1036
     BUFFER  1039
     ```

3. **`out_pass1.txt`**:
   - The output of Pass 1, including location counters and instructions.
   - Example:
     ```
     1000    COPY    START   1000
     1003    FIRST   STL     RETADR
     1006    CLOOP   JSUB    RDREC
     1009            LDA     #3
     100c            COMP    ZERO
     100f            JEQ     ENDFIL
     1012            JSUB    WRREC
     1015    ENDFIL  LDA     EOF
     ```

4. **`out_pass2.txt`**:
   - The output of Pass 2, containing the generated object code for each instruction.
   - Example:
     ```
     1000    COPY    START   1000    -
     1003    FIRST   STL     RETADR  141033
     1006    CLOOP   JSUB    RDREC   482039
     1009            LDA     #3      010003
     100c            COMP    ZERO    281030
     ```

5. **`HTE.txt`**:
   - The final HTE (Header, Text, End) record, used for executing the assembled program.
   - Example:
     ```
     H.XXCOPY.001000.00107a
     T.001000.141033.482039.010003.281030.301015.482061.3C1003.
     T.001015.00102a.0C1039.00102d.0C1036.1C2061.081033.4C0000.454f46.
     T.00102d.000003.000000.041030.001030.E0205d.
     T.002042.30203f.D8205d.281030.302057.549039.2C205e.38203f.101036.
     T.00205a.4C0000.C4.001000.041030.E02079.302064.509039.DC2079.
     T.002070.2C1036.382064.4C0000.05.
     E.001000
     ```

Each output file plays a role in verifying the assembly process and ensuring the correctness of the program. Review these files to understand the flow and results of the assembler.


