# mmap-load-test

A performance test playground for mmap vs. posix file reads

## How to run

This code requires MacOSX and XCode.

1. Run `create_data.sh` to create test files
2. Open the xcode project.
3. Click on "load-test" on the top left, choose "Edit Scheme...".  
Choose "Run".  
Look for "Use custom working directory", enter `${PROJECT_DIR}/data`
4. You can now run the test
