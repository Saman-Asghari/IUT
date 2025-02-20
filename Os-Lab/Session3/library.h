#ifndef LIBRARY_H
#define LIBRARY_H

void createFileWithPermission(const char * path, int permission);
void checkFile(const char * path, int permission);
void showFileInfo(const char * path);
void createFileList(const char * dirPath, const char * prefix, const char * ext, int from, int to);

#endif
