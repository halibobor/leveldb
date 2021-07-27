#include <cassert>
#include <iostream>
#include <string>
#include <chrono>
#include "leveldb/db.h"

int main() {
  leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;
  options.paranoid_checks = true;
  options.block_size = 4 * 1024;
  options.write_buffer_size = 32 * 1024 * 1024;
  options.max_open_files = 1000;
  // 打开一个leveldb数据库
  std::time_t s = std::time(0);  // t is an integer type
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/leveldb/account", &db);
  assert(status.ok());
  std::time_t e = std::time(0);  // t is an integer type
  std::cout << e-s << " seconds for open \n";
  int read_records = 0;
  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    read_records++;
  }
  assert(it->status().ok());  // Check for any errors found during the scan
  delete it;
  /*   assert(it->status().ok()); */ // Check for any errors found during the scan
   std::time_t ee = std::time(0);  // t is an integer type
   std::cout << ee-e << " seconds for Iterator \n";
   std::cout << read_records << " records....  \n";
   std::string val;
  bool is_ok = db->GetProperty("leveldb.approximate-memory-usage", &val);
  std::cout << is_ok << " is_ok \n";
  int mem_usage = std::stoi(val);
  std::cout << mem_usage << " mem_usage \n";
  delete db;
  return 0;
}
