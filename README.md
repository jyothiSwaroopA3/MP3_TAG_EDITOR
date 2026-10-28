# 🎵 MP3 Tag Reader and Editor in C

## 📌 Project Overview

The **MP3 Tag Reader and Editor** is a command-line application developed using C that allows users to read, display, and modify metadata (ID3 tags) stored in MP3 audio files.

MP3 files contain metadata such as song title, artist name, album name, release year, genre, and other information. This project provides an easy way to view and edit these details using file handling and binary data processing in C.

The project primarily focuses on working with **ID3v2 tags**, understanding file structures, and performing read and write operations on MP3 files.

## 🎯 Objectives

- To read and display metadata from MP3 files.
- To modify existing MP3 tag information.
- To understand binary file handling in C.
- To gain practical experience with file pointers and structures.
- To implement menu-driven functionality for reading and editing MP3 metadata.

## ✨ Features

### 📖 View MP3 Tags
- Display the metadata available in an MP3 file.
- Read information such as title, artist, album, year, and genre.

### ✏️ Edit MP3 Tags
- Modify supported metadata fields.
- Update the selected tag in the MP3 file.
- Preserve the remaining audio data while editing metadata.

### 🛠️ File Handling
- Open and process MP3 files in binary mode.
- Read and write metadata using file operations.
- Handle tag frames and their associated data.

## 🛠️ Technologies Used

- **Programming Language:** C
- **Concepts:** File Handling, Pointers, Structures, Dynamic Memory Allocation
- **File Processing:** Binary File Operations
- **Metadata Standard:** ID3 Tags
- **Development Tools:** GCC Compiler, Linux/WSL Terminal

## ⚙️ How It Works

1. The user provides an MP3 file.
2. The application reads the MP3 metadata.
3. The user selects the operation: view or edit tags.
4. For editing, the user selects a supported field and enters the updated value.
5. The application saves the modified metadata to the MP3 file.

## 📂 Project Structure

```text
MP3_TAG_EDITOR/
├── main.c
├── view.c
├── edit.c
├── header.h
├── Makefile
└── README.md
```

*The file structure may vary depending on the implementation.*

## 🚀 Compilation and Execution

### Compile

If your project includes a `Makefile`, run:

```bash
make
```

Alternatively, compile the source files directly:

```bash
gcc main.c edit.c view.c -o mp3tag
```

### Run

On Linux or WSL:

```bash
./mp3tag
```

On Windows, if compiled as an executable:

```bash
mp3tag.exe
```

Follow the on-screen menu to view or edit MP3 tags.

## 📚 Learning Outcomes

Through this project, I gained practical experience in:

- File handling and binary file processing in C.
- Understanding MP3 metadata and ID3 tag structures.
- Using pointers and structures for data management.
- Reading and modifying file contents.
- Developing menu-driven applications.
- Debugging and organizing a multi-file C project.

## 🔮 Future Enhancements

- Support for additional ID3 tag versions.
- Improved input validation and error handling.
- Support for editing more metadata
