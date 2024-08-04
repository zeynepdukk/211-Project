# Command Based Text Editor
This project is a command-based directory manager developed as a term project for CSE211.
## Features
#### File Listing: Read and list files from a specified directory.
#### Search by File Name: Search for files by their names.
#### Search by File Extension: Search for files by their extensions.
#### Search by File Size: Search for files by their sizes.
#### Remove by File Name: Remove files from the list by their names.
#### Update List: Refresh the list of files by reading the directory again.
#### Traverse List: Display files sorted by name, extension, or size.

## Code Structure
#### Node Class: Represents a file with attributes such as name, extension, and size. Maintains sorted lists by name, size, and extension.
#### printNode(): Prints information of a single node.
#### InsertNode(): Inserts nodes into sorted lists based on name, size, or extension.
#### TraverseBy(): Traverses and displays the list based on the specified sorting criteria.
#### readFromDirectory(): Reads files from a directory and populates the linked lists.
#### removeNode(): Removes a node from the specified list.
#### removeByFileName(): Removes a node by filename and updates all relevant lists.
## Example
To list the contents of a directory, enter the path of the directory (e.g., /home/user/documents).
Compile and run the program, then select the desired operation from the menu.
