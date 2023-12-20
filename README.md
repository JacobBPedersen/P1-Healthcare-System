## Testing
Specific functions have been selected for testing. To execute these tests, please adhere to the instructions provided below. CTest will be used to run these tests.

### Step 1: Create a Build Directory

This directory will contain all the build files.

```bash
mkdir build
```

### Step 2: Change Directory to 'build'

Navigate into the newly created `build` directory.

```bash
cd build
```

### Step 3: Run CMake

Generate the makefiles for your project. Ensure you are in the `build` directory and then run:

```bash
cmake ..
```

This command tells CMake to look for a `CMakeLists.txt` file in the parent directory and configure the project accordingly.

### Step 4: Compile the Project

Compile your project using the makefiles generated by CMake.

```bash
make
```

This command will compile the code based on the configurations provided.

### Step 5: Run Tests with CTest

Finally, execute the tests using CTest.

```bash
ctest
```

CTest will run all the tests and output the results.