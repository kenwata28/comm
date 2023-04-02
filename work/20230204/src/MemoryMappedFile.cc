#include <MemoryMappedFile.h>

#include "IndexOfKeyType.h"

using namespace key_type_counting;

namespace key_type_counting {

long long* MemoryMappedFile::operator[](int index) {
  const int idx = index_map_[index];
  if (idx < 0) {
    ErrorBox("something wrong opreater[]");
    exit(1);
  };
  return mapped_view_[idx];
}

const long long* const MemoryMappedFile::operator[](int index) const {
  const int idx = index_map_[index];
  if (idx < 0) {
    ErrorBox("something wrong opreater[]");
    exit(1);
  };
  return mapped_view_[idx];
}

bool MemoryMappedFile::EnableToLogKeytype(int i) const {
  return enable_to_log_keytype[i];
}

std::vector<int> MemoryMappedFile::PrepareIndexOfKeytype() const {
  std::vector<int> ans(kNumOfVK);
  int index = 0;
  for (int i = 0; i < kNumOfVK; i++) {
    ans[i] = -1;
    if (EnableToLogKeytype(i)) {
      ans[i] = index;
      index++;
    }
  }
  return ans;
}

bool MemoryMappedFile::LoadMappingHandleAndView() {
  // マッピング作成
  file_mapping_handle_ = CreateFileMapping(file_handle_, nullptr,
                                           PAGE_READWRITE, 0, size_, nullptr);
  if (file_mapping_handle_ == nullptr) {
    ErrorBox("Cannot create file mapping.");
    return false;
  }

  // マップされたビューを取得
  mapped_view_ = reinterpret_cast<long long(*)[NUM_OF_KIND]>(
      MapViewOfFile(file_mapping_handle_, FILE_MAP_ALL_ACCESS, 0, 0, size_));
  if (mapped_view_ == nullptr) {
    ErrorBox("Error: Cannot map view of file.");
    return false;
  }

  return true;
}

bool MemoryMappedFile::CreateFirst() {
  Close();

  // ファイル作成
  file_handle_ = CreateFileA(filename_.c_str(),
                             GENERIC_READ | GENERIC_WRITE,  // read and write
                             0,                             // 排他mode.
                             nullptr,
                             CREATE_ALWAYS,  // とにかくopen.
                             FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file_handle_ == INVALID_HANDLE_VALUE) {
    ErrorBox("Error: Cannot create file.");
    return false;
  }
  if (LoadMappingHandleAndView()) {
    // Initialise memory mapped file data
    for (int i = 0; i < 0xFF; i++) {
      int idx = index_map_[i];
      if (idx < 0) continue;
      mapped_view_[idx][TOTAL] = 100;
      mapped_view_[idx][MISS] = 0;
    }
    return true;
  }
  return false;
}

bool MemoryMappedFile::Open() {
  Close();

  // ファイルを開く
  file_handle_ = CreateFileA(filename_.c_str(),
                             GENERIC_READ | GENERIC_WRITE,  // read and write
                             0,                             // 排他mode
                             nullptr,
                             OPEN_EXISTING,  // when existing
                             FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file_handle_ == INVALID_HANDLE_VALUE) {
    ErrorBox("Error: Cannot open file.");
    return false;
  }
  return LoadMappingHandleAndView();
}

void MemoryMappedFile::Close() {
  if (mapped_view_ != nullptr) {
    UnmapViewOfFile(mapped_view_);
    mapped_view_ = nullptr;
  }

  if (file_mapping_handle_ != nullptr) {
    CloseHandle(file_mapping_handle_);
    file_mapping_handle_ = nullptr;
  }

  if (file_handle_ != INVALID_HANDLE_VALUE) {
    CloseHandle(file_handle_);
    file_handle_ = INVALID_HANDLE_VALUE;
  }
}
CountData* CountData::instance = nullptr;

}  // namespace key_type_counting
