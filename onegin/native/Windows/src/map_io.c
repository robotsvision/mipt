#include <map_io.h>

/*************************************************************
 * Private
 ************************************************************/

static HANDLE _GetFileHandle(const char filename[]) {
    return CreateFileA((char*)filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

static HANDLE _GetMapHandle(HANDLE sys0_handle) {
    return CreateFileMappingA(sys0_handle, NULL, PAGE_READONLY, 0, 0, NULL);
}

static LPCVOID _GetMapView(HANDLE sys1_handle) {
    return MapViewOfFile(sys1_handle, FILE_MAP_READ, 0, 0, 0);
}

static LONGLONG _GetFileSize(HANDLE sys0_handle) {
    LARGE_INTEGER size;
    if (!GetFileSizeEx(sys0_handle, &size)) {
        return -1;
    }
    return size.QuadPart;
}

/*************************************************************
 * Public
 ************************************************************/

oerror_t ofopen(const char filename[], ofile_t* file) {
    file->sys0_handle = _GetFileHandle(filename);
    if (file->sys0_handle == INVALID_HANDLE_VALUE) {
        return 1;
    }
    file->sys1_handle = _GetMapHandle(file->sys0_handle);
    if (file->sys1_handle == NULL) {
        CloseHandle(file->sys0_handle);
        return 2;
    }
    file->data_handle = _GetMapView(file->sys1_handle);
    if (file->data_handle == NULL) {
        CloseHandle(file->sys1_handle);
        CloseHandle(file->sys0_handle);
        return 3;
    }
    file->size = _GetFileSize(file->sys0_handle);
    if (file->size == -1) {
        UnmapViewOfFile(file->data_handle);
        CloseHandle(file->sys1_handle);
        CloseHandle(file->sys0_handle);
        return 4;
    }
    return OFILE_OK;
}

oerror_t lfget(char** pointer, ofile_t* file) {
    *pointer = (char*)(file->data_handle);
    return OFILE_OK;
}

oerror_t lfclose(ofile_t* file) {
    UnmapViewOfFile(file->data_handle);
    CloseHandle(file->sys1_handle);
    CloseHandle(file->sys0_handle);
    return OFILE_OK;
}