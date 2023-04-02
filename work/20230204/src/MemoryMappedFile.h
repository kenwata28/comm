#ifndef MEMORY_MAPPED_FILE_H_
#define MEMORY_MAPPED_FILE_H_

#include <windows.h>

#include <iostream>
// #include <stdexcept>
#include <algorithm>
#include <vector>

namespace key_type_counting {

enum KindOfCountingType { TOTAL = 0, MISS, NUM_OF_KIND };
const int kNumOfVK = 0xFF;  // virtual key の 種類.

//
//
//
//
//
class MemoryMappedFile {
 public:
  MemoryMappedFile(const std::string& filename)
      : filename_{filename},
        file_handle_(INVALID_HANDLE_VALUE),
        file_mapping_handle_(nullptr),
        mapped_view_(nullptr) {
    index_map_ = PrepareIndexOfKeytype();
    size_ = sizeof(long long) * NUM_OF_KIND * index_map_.size();
    if (!Open()) CreateFirst();
  }

  ~MemoryMappedFile() { Close(); }
  bool EnableToLogKeytype(int i) const;
  long long* operator[](int index);
  const long long* const operator[](int index) const;

 private:
  std::vector<int> PrepareIndexOfKeytype() const;
  bool LoadMappingHandleAndView();
  bool CreateFirst();
  bool Open();
  void Close();

  void ErrorBox(const char* txt) const {
    MessageBoxA(NULL, txt, "Error in MemoryMappedFile", MB_ICONERROR);
  }

 private:
  MemoryMappedFile() = delete;

 private:
  std::string filename_;
  HANDLE file_handle_;
  HANDLE file_mapping_handle_;
  long long (*mapped_view_)[NUM_OF_KIND];
  std::vector<int> index_map_;
  size_t size_ = 0;
};

class StructTypingData {
 public:
  int vkey;
  long long total_count;
  long long miss_count;
  double miss_rate;
  void Show() {
    char txt[256];
    sprintf(txt, "key(%d), %lld, %lld, %lf", vkey, total_count, miss_count,
            miss_rate);
    MessageBoxA(NULL, txt, "strcuct typing data", 0);
  }
};

//
//
//
//
//
class CountData {
 public:
  // これだけが data を変更できる.
  void CountUpTotal(int vkey) {
    if (mmf_.EnableToLogKeytype(vkey)) mmf_[vkey][TOTAL]++;
  }
  void CountUpMiss(int vkey) {
    if (mmf_.EnableToLogKeytype(vkey)) mmf_[vkey][MISS]++;
  }

  // analyzer
  std::vector<StructTypingData> AllStructTypingData() const {
    std::vector<StructTypingData> ans;
    for (int i : valid_keys_) {
      double rate = double(mmf_[i][MISS]) / mmf_[i][TOTAL];
      StructTypingData dat{i, mmf_[i][TOTAL], mmf_[i][MISS], rate};
      // dat.Show();
      ans.push_back(dat);
    }
    return ans;
  }

  void SortByMissRate(std::vector<StructTypingData>* vec) const {
    auto func = [](const StructTypingData& a, const StructTypingData& b) {
      return a.miss_rate > b.miss_rate;
    };
    std::sort(vec->begin(), vec->end(), func);
  }

  int TopMissKey(int order, double* rate, long long* total_count,
                 long long* miss_count) const {
    auto vec = AllStructTypingData();
    SortByMissRate(&vec);

    auto dat = vec.at(order);
    *rate = dat.miss_rate;
    *total_count = dat.total_count;
    *miss_count = dat.miss_count;
    return dat.vkey;
  }

  static CountData* GetInstance() {
    if (instance == nullptr) {
      instance = new CountData();
    }
    return instance;
  }

 private:
  // use as singleton
  CountData() : mmf_{MemoryMappedFile("type_count_buf.mmf")} {
    for (int i = 0; i < kNumOfVK; i++) {
      if (mmf_.EnableToLogKeytype(i)) valid_keys_.push_back(i);
    }
  }

 private:
  static CountData* instance;
  MemoryMappedFile mmf_;
  std::vector<int> valid_keys_;
};

}  // namespace key_type_counting

#endif  // MEMORY_MAPPED_FILE_H_
